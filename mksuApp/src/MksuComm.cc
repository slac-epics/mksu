#include <string.h> // memcpy
#include <iostream>
#include <sstream>
#include <epicsThread.h>
#include <alarm.h>

#include "MksuComm.h"
#include "Log.h"

MksuComm::MksuComm(std::string mksuPortName, MksuParam *params, int numParams) :
  _moduleNumber(21),
  _mksuPortName(mksuPortName),
  _sock(NULL),
  _commandCounter(0),
  _writeResponse(reinterpret_cast<char *>(&_writeResponseHeader)),
  _mutex(NULL),
  _badTaskIdCounter(0),
  _reconnectCounter(0) {
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

  _mutex = new epicsMutex();
}

MksuComm::~MksuComm() {
  delete [] _command;
  if (_mutex != NULL) {
    delete _mutex;
  }
}

void MksuComm::reconnect() {
  Log::getInstance() << Log::flagComm << Log::dpInfo;
  Log::getInstance() << "MksuComm::reconnect()" << Log::dp;

  if (pasynOctetSyncIO->disconnect(_sock) != asynSuccess) {
    Log::getInstance() << Log::flagComm << Log::dpError;
    Log::getInstance() << "MksuComm::reconnect()"
		       << " Failed to disconnect" << Log::dp;
    _sock = NULL;
  }

  if (pasynOctetSyncIO->connect(_mksuPortName.c_str(),
				0, &_sock, NULL) != asynSuccess) {
    Log::getInstance() << Log::flagComm << Log::dpError; 
    Log::getInstance() << "MksuComm::reconnect()"
		       << " Failed to connect" << Log::dp;
    _sock = NULL;
  }

  _reconnectCounter++;
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
	block.status = NO_ALARM;
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
  if (_mutex!=NULL) _mutex->lock();

  MksuBlock *block = getBlock(blockId);
  if (block == NULL) {
    if (_mutex!=NULL) _mutex->unlock();
    return false;
  }

  if (blockId == MKSU_FAST_ADC_WF_BLOCK ||
      blockId == MKSU_FAST_ADC_WF_BLOCK + block->address) {
    memcpy(value, &block->data[0], size * sizeof(epicsInt16));
  }
  else {
    memcpy(value, &block->data[address], size * sizeof(epicsInt16));
  }
  
  if (_mutex!=NULL) _mutex->unlock();
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
  if (_mutex!=NULL) _mutex->lock();
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

  if (status != asynSuccess) {
    Log::getInstance() << Log::flagCommWrite << Log::dpError;
    Log::getInstance() << "MksuComm::write(blockId="
		     << blockId << ", address=" << address 
		     << "value=" << value << ")"
		     << ": communication failed (status="
		     << (int) status << ")" << Log::dp;
    reconnect();
    if (_mutex!=NULL) _mutex->unlock();
    return false;
  }
				       
  if (_writeResponseHeader.taskId != _commandCounter) {
    Log::getInstance() << Log::flagCommWrite << Log::dpError;
    Log::getInstance() << "MksuComm::write(blockId="
		       << blockId << ", address=" << address 
		       << "value=" << value << ")"
		       << ": expected taskId of " << _commandCounter
		       << " got " << _writeResponseHeader.taskId
		       << " instead." << Log::dp;
    _badTaskIdCounter++;
    reconnect();
    if (_mutex!=NULL) _mutex->unlock();
    return false;
  }

  _commandCounter++;

  Log::getInstance() << Log::flagCommWrite << Log::dpInfo;
  Log::getInstance() << "MksuComm::write(blockId="
		     << blockId << ", address=" << address 
		     << ", value=" << value << "), numSent=" << (int) numSent
		     << ", responseLen=" << (int) responseLen
		     << ", eomReason=" << (int) eomReason
		     << Log::dp;

  if (_mutex!=NULL) _mutex->unlock();
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
  if (_mutex!=NULL) _mutex->lock();
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

  if (status != asynSuccess) {
    Log::getInstance() << Log::flagCommWrite << Log::dpError;
    Log::getInstance() << "MksuComm::write(blockId="
		       << blockId << ", address=" << address
		       << ", value[0]=" << value[0]
		       << ", size=" << size << ")"
		       << ": communication failed (status="
		       << (int) status << ")" << Log::dp;
    reconnect();
    if (_mutex!=NULL) _mutex->unlock();
    return false;
  }
				       
  if (_writeResponseHeader.taskId != _commandCounter) {
    Log::getInstance() << Log::flagCommWrite << Log::dpError;
    Log::getInstance() << "MksuComm::write(blockId="
		       << blockId << ", address=" << address
		       << ", value[0]=" << value[0]
		       << ", size=" << size << ")"
		       << ": expected taskId of " << _commandCounter
		       << " got " << _writeResponseHeader.taskId
		       << " instead." << Log::dp;
    _badTaskIdCounter++;
    reconnect();
    if (_mutex!=NULL) _mutex->unlock();
    return false;
  }

  _commandCounter++;

  Log::getInstance() << Log::flagCommWrite << Log::dpInfo;
  Log::getInstance() << "MksuComm::write(blockId="
		     << blockId << ", address=" << address
		     << ", value[0]=" << value[0]
		     << ", size=" << size << ")"
		     << " numSent=" << (int) numSent
		     << ", responseLen=" << (int) responseLen
		     << ", eomReason=" << (int) eomReason
		     << Log::dp;
  if (_mutex!=NULL) _mutex->unlock();
  return true;
}

int MksuComm::refresh() {
  return NO_ALARM;
}

/**
 * Update the memory for the given blockId. A UDP read command is sent
 * to the MKSU and the block is refreshed with the MKSU response.
 *
 * @param blockId id of the block to be updated (greater than 0x40)
 * @return -1 if the blockId is invalid, NO_ALARM if the refresh was
 * successful, COMM_ALARM if there is a failure communicating to
 * the MKSU, or UDF_ALARM if the response from the MKSU does not
 * match the request.
 * 
 * @author L.Piccoli
 */
int MksuComm::refresh(int blockId) {
  if (_mutex!=NULL) _mutex->lock();
  time_t now = time(0);

  MksuBlock *block = getBlock(blockId);
  if (block == NULL) {
    if (_mutex!=NULL) _mutex->unlock();
    return -1;
  }
  Log::getInstance() << Log::flagComm << Log::dpInfo;
  Log::getInstance() << "MksuComm::refresh(blockId="
		     << blockId << "): last refreshed "
		     << now - block->time << " seconds ago."
		     << " Block address " << (int) block << Log::dp;

  // This is a special block, used only to generate the
  // plot trace lines for the Fast ADC waveforms!
  if (blockId == MKSU_FAST_ADC_WF_PLOT_BLOCK) {
    int status = refreshPlotBlock(block);
    block->time = now;
    if (_mutex!=NULL) _mutex->unlock();
    return status;
  }

  // Reflesh block only every couple seconds, return the status
  // of the previous reflesh
  if (block->time <= now - 4) {
    if (_mutex!=NULL) _mutex->unlock();
    return block->status;
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
    _commandHeader->messageType = MKSU_FAST_ADC_WF_BLOCK;
  }

  asynStatus status;
  size_t numSent;
  size_t responseLen;
  int eomReason;
  
  int tentative = 0;
  int sleepTime = 0;
  status = asynError;
  while (tentative < 10 && status != asynSuccess) {
    status = pasynOctetSyncIO->writeRead(_sock, _command, sizeof(MksuUdpHeader),
					 receiveMessage, receiveSize, 1, /* time out */
					 &numSent, &responseLen, &eomReason);
    if (tentative > 0) {
      Log::getInstance() << Log::flagComm << Log::dpError;
      Log::getInstance() << "ERROR: MksuComm::refresh(blockId="
			 << blockId << "): communication failed (status="
			 << (int) status << ") retrying." << Log::dp;
    }
    if (status != asynSuccess) {
      pasynOctetSyncIO->flush(_sock);
      epicsThreadSleep(sleepTime);
    }
    tentative++;
    sleepTime++;
  }

  if (status != asynSuccess) {
    Log::getInstance() << Log::flagComm << Log::dpError;
    Log::getInstance() << "ERROR: MksuComm::refresh(blockId="
		       << blockId << "): communication failed (status="
		       << (int) status << ")" << Log::dp;
    block->status = COMM_ALARM;
    reconnect();
    if (_mutex!=NULL) _mutex->unlock();
    return COMM_ALARM;
  }
				       
  if (block->header->taskId != _commandCounter) {
    Log::getInstance() << Log::flagComm << Log::dpError;
    Log::getInstance() << "MksuComm::reflesh(blockId="
		       << blockId << ")"
		       << ": expected taskId of " << _commandCounter
		       << " got " << _writeResponseHeader.taskId
		       << " instead." << Log::dp;
    Log::getInstance() << "MksuComm::refresh(blockId="
		       << blockId << "), address="
		       << _commandHeader->address
		       << ", numSent=" << (int) numSent
		       << ", responseLen=" << (int) responseLen
		       << ", eomReason=" << (int) eomReason
		       << ", status=" << (int) status
		       << Log::dp;
    block->status = UDF_ALARM;
    _badTaskIdCounter++;
    reconnect();
    if (_mutex!=NULL) _mutex->unlock();
    return UDF_ALARM;
  }

  _commandCounter++;

  Log::getInstance() << Log::flagComm << Log::dpInfo;
  Log::getInstance() << "MksuComm::refresh(blockId="
		     << blockId << "), address="
		     << _commandHeader->address
		     << ", numSent=" << (int) numSent
		     << ", responseLen=" << (int) responseLen
		     << ", eomReason=" << (int) eomReason
		     << ", status=" << (int) status
		     << Log::dp;

  block->time = now;
  block->status = NO_ALARM;

  printBlock(blockId);
  if (_mutex!=NULL) _mutex->unlock();
  return NO_ALARM;
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
  details << "Reconnect Counter: " << _reconnectCounter << std::endl;
  details << "Bad taskId Counter: " << _badTaskIdCounter << std::endl;
  details << std::endl;
}

int MksuComm::refreshPlotBlock(MksuBlock *block) {
  MksuBlock *sourceBlock = getBlock(0x44);

  if (block == NULL) {
    return -1;
  }

  if (sourceBlock->status != NO_ALARM) {
    return sourceBlock->status;
  }

  for (int i = 0; i < 4 * 4; i++) {
    block->data[i * 2] = sourceBlock->data[i+1];
    block->data[i * 2 + 1] = sourceBlock->data[i+1];
  }

  return NO_ALARM;
}
