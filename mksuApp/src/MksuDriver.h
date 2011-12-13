#include <string>
#include <map>
#include <stdio.h>
#include <asynPortDriver.h>
#include <MksuParam.h> // <- Automatically generated
#include "MksuComm.h"

#ifndef MKSUDRIVER_H
#define MKSUDRIVER_H

typedef std::map<int, MksuParam *> ParamMap;

class MksuDriver : public asynPortDriver {
public:
  MksuDriver(const char *portName, const char *mksuPortName);
  virtual ~MksuDriver();

  virtual asynStatus readInt8Array(asynUser *pasynUser, epicsInt8 *value, 
				   size_t nElements, size_t *nIn);
  virtual asynStatus readInt16Array(asynUser *pasynUser, epicsInt16 *value,
				    size_t nElements, size_t *nIn);
  virtual asynStatus readInt32(asynUser *pasynUser, epicsInt32 *value);
  virtual asynStatus writeInt16Array(asynUser *pasynUser, epicsInt16 *value,
				     size_t nElements);
  virtual asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);

  virtual void report(FILE *fp, int details);

 private:
  MksuParam *getParam(int key);

  ParamMap _paramMap;
  std::string _mksuPortName;
  MksuComm *_comm;
};

#endif
