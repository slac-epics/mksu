#include "Log.h"
#include "MksuDriver.h"
#include "MksuParamList.h" // <- Automatically generated

#include <iostream>

#include <epicsTypes.h>
#include <epicsExport.h>
#include <drvSup.h>

MksuDriver::MksuDriver(const char *portName, const char *mksuPortName) :
  asynPortDriver(portName, 1, MKSU_NUM_PARAMS,
		 asynInt32Mask | asynInt16ArrayMask | asynDrvUserMask, // interfaceMask
		 asynInt32Mask | asynInt16ArrayMask,                   // interruptMask
		 ASYN_CANBLOCK | ASYN_MULTIDEVICE,                     // asynFlags
		 1, 0, 0),           // autoConnect, priority, stackSize
  _mksuPortName(mksuPortName),
  _comm(mksuPortName) {
  Log::getInstance() << Log::flagGeneral << Log::dpInfo << "# Creating MKSU object" << Log::cout;
  for (int i = 0; i < MKSU_NUM_PARAMS; i++) {
    createParam(MksuParams[i].name.c_str(), MksuParams[i].type, &MksuParams[i].id);
    _paramMap.insert(std::pair<int, MksuParam *>(MksuParams[i].id, &MksuParams[i]));
  }
}

MksuDriver::~MksuDriver() {
}

MksuParam *MksuDriver::getParam(int key) {
  ParamMap::iterator it = _paramMap.find(key);
  if (it == _paramMap.end()) {
    Log::getInstance() << Log::flagAsyn << Log::dpError;
    Log::getInstance() << "ERROR: MksuDriver::getParam(key="
		       << key << "): invalid key (reason).\n" << Log::dp;
    return NULL;
  }

  return it->second;
}  

asynStatus MksuDriver::readInt32(asynUser *pasynUser, epicsInt32 *value) {
  Log::getInstance() << Log::flagAsyn << Log::dpInfo;
  Log::getInstance() << "MksuDriver::readInt32(reason="
		     << pasynUser->reason
		     << ")\n" << Log::dp;
  // First find the parameter in the _paramMap using the reason (key) field
  MksuParam *param = getParam(pasynUser->reason);
  if (param == NULL) {
    return asynError;
  }

  if (_comm.read(param->blockId, param->address, *value)) {
    return asynSuccess;
  }
  else {
    return asynError;
  }
}

asynStatus MksuDriver::writeInt32(asynUser *pasynUser, epicsInt32 value) {
  Log::getInstance() << Log::flagAsyn << Log::dpInfo;
  Log::getInstance() << "MksuDriver::writeInt32(reason="
		     << pasynUser->reason << ", value=" << value
		     << ")\n" << Log::dp;

  // First find the parameter in the _paramMap using the reason (key) field
  MksuParam *param = getParam(pasynUser->reason);
  if (param == NULL) {
    return asynError;
  }

  if (_comm.write(param->blockId, param->address, value)) {
    return asynSuccess;
  }
  else {
    return asynError;
  }
}

void MksuDriver::report(FILE *fp, int details) {
  fprintf(fp, "%s: driver report - %s\n",
	  portName, _mksuPortName.c_str());

  Log::getInstance() << Log::flagGeneral << Log::dpInfo
		     << "\n================== MKSU Parameters ====================\n";
  
  Log::getInstance() << "Name:\t\t\tblockId\taddress\tsize\tid\n";

  for (ParamMap::iterator it = _paramMap.begin();
       it != _paramMap.end(); it++) {
    MksuParam *param = (*it).second;
    Log::getInstance() << param->name.c_str() << ":\t"
		       << param->blockId << "\t"
		       << param->address << "\t"
		       << param->size << "\t"
		       << param->id << "\n";
  }


  Log::getInstance() << Log::dp;
  

  asynPortDriver::report(fp, details);
}

