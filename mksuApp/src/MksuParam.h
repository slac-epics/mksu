// Header file generated from MksuList.map on Tue, 07 May 2013 23:36:43 +0000

#ifndef MKSUPARAM_H
#define MKSUPARAM_H

// Struct that holds register information. The id field
// is used by asyn to connect with the actual asyn parameter
typedef struct {
  int blockId; // MKSU FPGA Block
  asynParamType type; // Defined in asynPortDriver.h
  long address; // Starting address (offset) within the FPGA block
  int conversion; // 0 for unsigned, 1 for signed int 16 (requires conversion)
  long size; // Number of bytes
  std::string name; // Name given in the INP/OUT asyn record field
  int id; // This is assigned by asynPortDriver::createParam()
} MksuParam;


#endif
