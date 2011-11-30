// Header file generated from MksuRegister.map on Tue, 29 Nov 2011 22:35:07 +0000

#ifndef MKSUPARAM_H
#define MKSUPARAM_H

// Struct that holds register information. The id field
// is used by asyn to connect with the actual asyn parameter
typedef struct {
  int blockId; // MKSU FPGA Block
  asynParamType type; // Defined in asynPortDriver.h
  long address; // Starting address (offset) within the FPGA block
  long size; // Number of bytes
  std::string name; // Name given in the INP/OUT asyn record field
  int id; // This is assigned by asynPortDriver::createParam()
} MksuParam;


#endif
