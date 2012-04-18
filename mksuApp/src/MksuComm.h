#include <string>
#include <map>
#include <stdio.h>
#include <time.h>
#include <asynPortDriver.h>
#include <asynOctetSyncIO.h>
#include "MksuParam.h"

#ifndef MKSUCOMM_H
#define MKSUCOMM_H

const int MKSU_MAX_BLOCK_SIZE = 10 * 1024; // 10K block size (more than enough!)
const int MKSU_MAX_COMMAND_SIZE = 1024;


typedef struct {
  unsigned char messageVersion;
  unsigned char modulatorNumber;
  unsigned char messageType; /* BlockId */
  unsigned char taskId; /* MksuComm counter */
  unsigned short address;
  unsigned short count;
} MksuUdpHeader;

typedef struct MksuBlock {
  int size;
  long address;
  unsigned short *memory;
  MksuUdpHeader *header;
  unsigned short *data;
  time_t time; // Last update time
  int status; // Communication status (NO_ALARM/UDF_ALARM/COMM_ALARM)
} MksuBlock;

typedef std::map<int, MksuBlock> BlockMap;

const int MKSU_FAST_ADC_WF_BLOCK = 0x61;
const int MKSU_FAST_ADC_WF_PLOT_BLOCK = 0x70;

/**
 * Class MksuComm
 *
 * This class is responsible for communicating with the MKSU unit
 * using the proper UDP asyn port specified in its constructor.
 *
 * A copy of the MKSU read memory is maintained and refreshed
 * periodically.
 *
 * This class provides methods to read and write individual MKSU
 * registers. The read method returns the latest value received
 * from the MKSU. The write method immediately sends the command
 * to the MKSU.
 *
 * @author L.Piccoli
 */
class MksuComm {
public:
  MksuComm(std::string mksuPortName, MksuParam *params, int numParams);
  virtual ~MksuComm();

  bool read(int blockId, long address, epicsInt32 &value);
  bool read(int blockId, long address, epicsInt8 *value, int size);
  bool read(int blockId, long address, epicsInt16 *value, int size);
  bool write(int blockId, long address, epicsInt32 value);
  bool write(int blockId, long address, epicsInt16 *value, int size);

  int refresh();
  int refresh(int blockId);

  void report(std::ostringstream &details);

 private:
  void createBlockMap(MksuParam *params, int numParams);
  MksuBlock *getBlock(int blockId);
  void printBlock(int blockId);
  int refreshPlotBlock(MksuBlock *block);

  /** MKSU module number (set in hardware) */
  char _moduleNumber;

  /** Asyn port name used to create the socket to talk to the MKSU */
  std::string _mksuPortName;

  /** "Socket" connecting to the MKSU */
  asynUser *_sock;

  /** Map containing a copy of all MKSU memory blocks */
  BlockMap _blockMap;

  /** Message used to send read/write commands */
  char *_command;

  /** Command header (points to the beginning of _command) */
  MksuUdpHeader *_commandHeader;

  /** Command data (points to just after the header in _command) */
  unsigned short *_commandData;

  /** Counter used to check the response to a command */
  unsigned char _commandCounter;

  /** Memory block to receive response of write commands */
  MksuUdpHeader _writeResponseHeader;
  char *_writeResponse;
};

#endif
