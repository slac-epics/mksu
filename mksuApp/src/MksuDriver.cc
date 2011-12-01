#include "Log.h"
#include "MksuDriver.h"
#include "MksuParamList.h" // <- Automatically generated

#include <iostream>
#include <sstream>

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
  _comm(mksuPortName, &MksuParams[0], MKSU_NUM_PARAMS) {
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
		       << key << "): invalid key (reason)." << Log::dp;
    return NULL;
  }

  return it->second;
}  

asynStatus MksuDriver::readInt8Array(asynUser *pasynUser, epicsInt8 *value, 
				     size_t nElements, size_t *nIn) {
  Log::getInstance() << Log::flagAsyn << Log::dpInfo;
  Log::getInstance() << "MksuDriver::readInt8Array(reason="
		     << pasynUser->reason
		     << ")" << Log::dp;
  return asynError;
}

/**
 * This method is called only when the associated record is processed, i.e.
 * a `caget PV` will not cause the driver to read the latest value from 
 * the MKSU. Either the scan field of the record must be set to some periodic
 * value or one must do a `caput PV.PROC 1`.
 *
 * The whole MKSU memory block is updated, but that does not mean all the
 * PVs get updated. The only PV to get new values is the one that caused
 * this method to be invoked.
 * 
 * @author L.Piccoli
 */
asynStatus MksuDriver::readInt32(asynUser *pasynUser, epicsInt32 *value) {
  Log::getInstance() << Log::flagAsyn << Log::dpInfo;
  Log::getInstance() << "MksuDriver::readInt32(reason="
		     << pasynUser->reason
		     << ")" << Log::dp;
  // First find the parameter in the _paramMap using the reason (key) field
  MksuParam *param = getParam(pasynUser->reason);
  if (param == NULL) {
    return asynError;
  }

  _comm.refresh(param->blockId);

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
		     << ")" << Log::dp;

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

void MksuDriver::report(FILE *fp, int reportDetails) {
  fprintf(fp, "%s: driver report - %s\n",
	  portName, _mksuPortName.c_str());

  std::ostringstream details;

  details << "\n================== MKSU Parameters ====================\n";
  
  details << "Name:\t\t\tblockId\taddress\tsize\tid\n";

  for (ParamMap::iterator it = _paramMap.begin();
       it != _paramMap.end(); it++) {
    MksuParam *param = (*it).second;
    details << param->name.c_str() << ":\t";
    if (param->name.length() < 12) {
      details << "\t";
      if (param->name.length() < 7) {
	details << "\t";
      }
    }

    details << param->blockId << "\t"
	    << param->address << "\t"
	    << param->size << "\t"
	    << param->id << "\t";
    if (param->size == 1) {
      epicsInt32 value = -1;
      if (_comm.read(param->blockId, param->address, value)) {
	details << " latest read: " << value;
      }
    }
    details << "\n";
  }

  Log::getInstance() << Log::flagGeneral << Log::dpInfo << details.str().c_str() << Log::dp;

  asynPortDriver::report(fp, reportDetails);
}

