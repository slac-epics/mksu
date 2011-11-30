#include <string>
#include <map>
#include <stdio.h>
#include <asynPortDriver.h>

#ifndef MKSUCOMM_H
#define MKSUCOMM_H

class MksuComm {
public:
  MksuComm(std::string mksuPortName);
  virtual ~MksuComm();

  bool read(int blockId, long address, epicsInt32 &value);
  bool write(int blockId, long address, epicsInt32 value);

 private:
  std::string _mksuPortName;
};

#endif
