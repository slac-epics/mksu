#include <string.h> // memcpy
#include <iostream>
#include <sstream>

#include "MksuComm.h"
#include "Log.h"

MksuComm::MksuComm(std::string mksuPortName, MksuParam *params, int numParams) :
  _moduleNumber(21),
  _mksuPortName(mksuPortName),
  _sock(NULL),
  _commandCounter(0),
  _writeResponse(reinterpret_cast<char *>(&_writeResponseHeader)) {
  if (pasynOctetSyncIO->connect(_mksuPortName.c_str(),
				0, &_sock, NULL) != asynSuccess) {
    Log::getInstance() << Log::flagComm << Log::dpError;
    Log::getInstance() << "MksuComm::MksuComm(port="
		       << _mksuPortName.c_str() << ")" << Log::dp;

    _sock = NULL;
    throw std::exception();
  }

  createBlockMap(params, numParams);

  _command = new char[MKSU_MAX_COMMAND_SIZE];
  _commandHeader = reinterpret_cast<MksuUdpHeader *>(_command);
  _commandData = reinterpret_cast<unsigned short *>(_commandHeader + 1);
}

MksuComm::~MksuComm() {
  delete [] _command;
}

/**
 * Create a map of memory blocks keyed by the MKSU blockId.
 *
 * Each memory block is a copy of the equivalend blockId in
 * the MKSU.
 *
 * Only the read blocks are stored here (blockId > 0x40)
 *
 * @author L.Piccoli
 */
void MksuComm::createBlockMap(MksuParam *params, int numParams) {
  for (int i = 0; i < numParams; i++) {
    // Create a block only for reading operations
    int blockId = params[i].blockId;
    if (blockId > 0x40) {
      BlockMap::iterator it = _blockMap.find(blockId);
      if (it == _blockMap.end()) {
	MksuBlock block;
	block.memory = new unsigned short[MKSU_MAX_BLOCK_SIZE];
	block.size = MKSU_MAX_BLOCK_SIZE;
	block.address = params[i].address;
	block.header = reinterpret_cast<MksuUdpHeader *>(block.memory);
	block.data = reinterpret_cast<unsigned short *>(block.header + 1);
	block.time = time(0);
	_blockMap.insert(std::pair<int, MksuBlock>(blockId, block));
      }
    }
  }
}

/**
 * Used to retrieve an MKSU read block kept by the driver.
 *
 * @return a pointer to the MksuBlock that describes the given
 * blockId or NULL if blockId is not valid.
 * @author L.Piccoli
 */
MksuBlock *MksuComm::getBlock(int blockId) {
  BlockMap::iterator it = _blockMap.find(blockId);
  if (it == _blockMap.end()) {
    Log::getInstance() << Log::flagComm << Log::dpError;
    Log::getInstance() << "ERROR: MksuComm::getBlock(blockId="
		       << blockId << "): invalid blockId." << Log::dp;
    return NULL;
  }

  return &(it->second);
}  

/**
 * Copies the value stored at the given address of the given blockId
 * to the specified value.
 *
 * @param blockId the MKSU memory block
 * @param address location of the value to be read
 * @param value returning parameter
 * @return true if block and value were found, false if blockId is
 * not valid (TODO: check address)
 * @author L.Piccoli
 */
bool MksuComm::read(int blockId, long address, epicsInt32 &value) {
  Log::getInstance() << Log::flagComm << Log::dpInfo;
  Log::getInstance() << "MksuComm::read(blockId="
		     << blockId << ", address=" << address
		     << ")" << Log::dp;

  MksuBlock *block = getBlock(blockId);
  if (block == NULL) {
    return false;
  }

  value = block->data[address];

  return true;
}

/**
 * Copies a sequence of values stored at the given address of the
 * given blockId to the memory area pointed by the parameter value.
 *
 * @param blockId the MKSU memory block
 * @param address starting location of the values to be read
 * @param value points to the area where values are getting copied
 * @param size number of items to be copied (of sizeof(epicsInt8))
 * @return true if block and value were found, false if blockId is
 * not valid (TODO: check address)
 * @author L.Piccoli
 */
bool MksuComm::read(int blockId, long address, epicsInt8 *value, int size) {
  MksuBlock *block = getBlock(blockId);
  if (block == NULL) {
    return false;
  }

  memcpy(value, &block->data[address], size * sizeof(epicsInt8));
  
  return true;
}

/**
 * Copies a sequence of values stored at the given address of the
 * given blockId to the memory area pointed by the parameter value.
 *
 * @param blockId the MKSU memory block
 * @param address starting location of the values to be read
 * @param value points to the area where values are getting copied
 * @param size number of items to be copied (of sizeof(epicsInt16))
 * @return true if block and value were found, false if blockId is
 * not valid (TODO: check address)
 * @author L.Piccoli
 */
bool MksuComm::read(int blockId, long address, epicsInt16 *value, int size) {
  MksuBlock *block = getBlock(blockId);
  if (block == NULL) {
    return false;
  }

  if (blockId == MKSU_FAST_ADC_WF_BLOCK ||
      blockId == MKSU_FAST_ADC_WF_BLOCK + block->address) {
    memcpy(value, &block->data[0], size * sizeof(epicsInt16));
  }
  else {
    memcpy(value, &block->data[address], size * sizeof(epicsInt16));
  }
  
  return true;
}

/**
 * Sends a write command to the MKSU, the specified value is writen
 * to the given block at the given address.
 *
 * @param blockId the MKSU memory block
 * @param address location of the value to be read
 * @param value data to be written out
 * @return true if block and value were found, false if blockId is
 * not valid (TODO: check address)
 * @author L.Piccoli
 */
bool MksuComm::write(int blockId, long address, epicsInt32 value) {
  Log::getInstance() << Log::flagCommWrite << Log::dpInfo;
  Log::getInstance() << "MksuComm::write(blockId="
		     << blockId << ", address=" << address
		     << ", value=" << value
		     << ")" << Log::dp;

  _commandHeader->messageVersion = 0x01;
  _commandHeader->modulatorNumber = _moduleNumber;
  _commandHeader->messageType = blockId;
  _commandHeader->taskId = _commandCounter;
  _commandHeader->address = address;
  _commandHeader->count = sizeof(unsigned short) / 2;

  _commandData[0] = value;

  asynStatus status;
  size_t numSent;
  size_t responseLen;
  int eomReason;
  
  status = pasynOctetSyncIO->writeRead(_sock, _command,
				       sizeof(MksuUdpHeader) + sizeof(unsigned short),
				       _writeResponse, sizeof(MksuUdpHeader), 1, /* time out */
				       &numSent, &responseLen, &eomReason);

  if (_writeResponseHeader.taskId != _commandCounter) {
    Log::getInstance() << Log::flagCommWrite << Log::dpError;
    Log::getInstance() << "MksuComm::write(blockId="
		       << blockId << ", address=" << address 
		       << "value=" << value << ")"
		       << ": expected taskId of " << _commandCounter
		       << " got " << _writeResponseHeader.taskId
		       << " instead." << Log::dp;
    return false;
  }

  _commandCounter++;

  if (status != asynSuccess) {
    Log::getInstance() << Log::flagCommWrite << Log::dpError;
    Log::getInstance() << "MksuComm::write(blockId="
		     << blockId << ", address=" << address 
		     << "value=" << value << ")"
		     << ": communication failed (status="
		     << (int) status << ")" << Log::dp;
    return false;
  }
				       
  Log::getInstance() << Log::flagCommWrite << Log::dpInfo;
  Log::getInstance() << "MksuComm::write(blockId="
		     << blockId << ", address=" << address 
		     << ", value=" << value << "), numSent=" << (int) numSent
		     << ", responseLen=" << (int) responseLen
		     << ", eomReason=" << (int) eomReason
		     << Log::dp;

  return true;
}

/**
 * Sends a write command to the MKSU, the specified value is writen
 * to the given block at the given address.
 *
 * @param blockId the MKSU memory block
 * @param address location of the value to be read
 * @param value array of epicsInt16 to be written out
 * @param size number of elements in the value array
 * @return true if block and value were found, false if blockId is
 * not valid (TODO: check address)
 * @author L.Piccoli
 */
bool MksuComm::write(int blockId, long address, epicsInt16 *value, int size) {
  Log::getInstance() << Log::flagCommWrite << Log::dpInfo;
  Log::getInstance() << "MksuComm::write(blockId="
		     << blockId << ", address=" << address
		     << ", value[0]=" << value[0]
		     << ", size=" << size << ")" << Log::dp;

  _commandHeader->messageVersion = 0x01;
  _commandHeader->modulatorNumber = _moduleNumber;
  _commandHeader->messageType = blockId;
  _commandHeader->taskId = _commandCounter;
  _commandHeader->address = address;
  _commandHeader->count = size;

  memcpy(&_commandData[0], value, size * sizeof(epicsInt16));

  asynStatus status;
  size_t numSent;
  size_t responseLen;
  int eomReason;
  
  status = pasynOctetSyncIO->writeRead(_sock, _command,
				       sizeof(MksuUdpHeader) + size * sizeof(epicsInt16),
				       _writeResponse, sizeof(MksuUdpHeader), 1, /* time out */
				       &numSent, &responseLen, &eomReason);

  if (_writeResponseHeader.taskId != _commandCounter) {
    Log::getInstance() << Log::flagCommWrite << Log::dpError;
    Log::getInstance() << "MksuComm::write(blockId="
		       << blockId << ", address=" << address
		       << ", value[0]=" << value[0]
		       << ", size=" << size << ")"
		       << ": expected taskId of " << _commandCounter
		       << " got " << _writeResponseHeader.taskId
		       << " instead." << Log::dp;
    return false;
  }

  _commandCounter++;

  if (status != asynSuccess) {
    Log::getInstance() << Log::flagCommWrite << Log::dpError;
    Log::getInstance() << "MksuComm::write(blockId="
		       << blockId << ", address=" << address
		       << ", value[0]=" << value[0]
		       << ", size=" << size << ")"
		       << ": communication failed (status="
		       << (int) status << ")" << Log::dp;
    return false;
  }
				       
  Log::getInstance() << Log::flagCommWrite << Log::dpInfo;
  Log::getInstance() << "MksuComm::write(blockId="
		     << blockId << ", address=" << address
		     << ", value[0]=" << value[0]
		     << ", size=" << size << ")"
		     << " numSent=" << (int) numSent
		     << ", responseLen=" << (int) responseLen
		     << ", eomReason=" << (int) eomReason
		     << Log::dp;

  return true;
}

void MksuComm::refresh() {
}

/**
 * Update the memory for the given blockId. A UDP read command is sent
 * to the MKSU and the block is refreshed with the MKSU response.
 *
 * @param blockId id of the block to be updated (greater than 0x40)
 * @ author L.Piccoli
 */
void MksuComm::refresh(int blockId) {
  time_t now = time(0);

  MksuBlock *block = getBlock(blockId);
  if (block == NULL) {
    return;
  }
  Log::getInstance() << Log::flagComm << Log::dpInfo;
  Log::getInstance() << "MksuComm::refresh(blockId="
		     << blockId << "): last refreshed "
		     << now - block->time << " seconds ago."
		     << " Block address " << (int) block << Log::dp;

  // Reflesh block only every couple seconds
  if (block->time <= now - 4) {
    return;
  }
  else {
    Log::getInstance() << Log::flagComm << Log::dpDebug;
    Log::getInstance() << "MksuComm::refresh(blockId="
		       << blockId << "): refresh after 2 seconds." << Log::dp;
  }

  char *receiveMessage = reinterpret_cast<char *>(block->memory);
  int receiveSize = block->size;

  _commandHeader->messageVersion = 0x01;
  _commandHeader->modulatorNumber = _moduleNumber;
  _commandHeader->messageType = blockId;
  _commandHeader->taskId = _commandCounter;

  // Address must be zero, otherwise the MKSU will return data
  // from the specified address
  _commandHeader->address = 0;
  _commandHeader->count = 0;

  // The starting address is relevant only for the Fast ADC Waveforms
  if (blockId == MKSU_FAST_ADC_WF_BLOCK ||
      blockId == MKSU_FAST_ADC_WF_BLOCK + block->address) {
    _commandHeader->address = block->address;
  }

  asynStatus status;
  size_t numSent;
  size_t responseLen;
  int eomReason;
  
  status = pasynOctetSyncIO->writeRead(_sock, _command, sizeof(MksuUdpHeader),
				       receiveMessage, receiveSize, 1, /* time out */
				       &numSent, &responseLen, &eomReason);

  if (block->header->taskId != _commandCounter) {
    Log::getInstance() << Log::flagComm << Log::dpError;
    Log::getInstance() << "MksuComm::reflesh(blockId="
		       << blockId << ")"
		       << ": expected taskId of " << _commandCounter
		       << " got " << _writeResponseHeader.taskId
		       << " instead." << Log::dp;
    return;
  }

  _commandCounter++;

  if (status != asynSuccess) {
    Log::getInstance() << Log::flagComm << Log::dpError;
    Log::getInstance() << "ERROR: MksuComm::refresh(blockId="
		       << blockId << "): communication failed (status="
		       << (int) status << ")" << Log::dp;
    return;
  }
				       
  Log::getInstance() << Log::flagComm << Log::dpInfo;
  Log::getInstance() << "MksuComm::refresh(blockId="
		     << blockId << "), numSent=" << (int) numSent
		     << ", responseLen=" << (int) responseLen
		     << ", eomReason=" << (int) eomReason
		     << Log::dp;

  block->time = now;
  /*
  if (blockId == MKSU_FAST_ADC_WF_BLOCK ||
      blockId == MKSU_FAST_ADC_WF_BLOCK + block->address) {
    std::ostringstream info;
    
    int offset = 0;
    info << "=== Block " << blockId << " ===" << std::endl;
    for (int i = 0; i < 512/32; i++) {
      for (int j = 0; j < 32; j++) {
	info << std::hex << block->data[offset] << " ";
	offset++;
      }
      info << std::endl;
    }
    info << "..." << std::endl;
    
    Log::getInstance() << Log::flagComm << Log::dpWarn
		       << info.str().c_str() << Log::dp;
  }
  */

  printBlock(blockId);
}

void MksuComm::printBlock(int blockId) {
  MksuBlock *block = getBlock(blockId);
  if (block == NULL) {
    return;
  }

  std::ostringstream info;

  int offset = 0;
  info << "=== Block " << blockId << " ===" << std::endl;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 10; j++) {
      info << std::hex << block->data[offset] << " ";
      offset++;
    }
    info << std::endl;
  }
  info << "..." << std::endl;

  Log::getInstance() << Log::flagComm << Log::dpDebug
		     << info.str().c_str() << Log::dp;
}

void MksuComm::report(std::ostringstream &details) {
  details << "=== MKSU Block last update time ===" << std::endl;

  for (BlockMap::iterator it = _blockMap.begin();
       it != _blockMap.end(); it++) {
    time_t now = time(0);
    details << it->first << ":\t"
	    << now - (it->second).time << " seconds ago."
	    << std::endl;
  }
  details << std::endl;
}
