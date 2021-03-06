#include "Log.h"
#include "MksuDriver.h"
#include "MksuParamList.h" // <- Automatically generated

#include <iostream>
#include <sstream>

#include <epicsTypes.h>
#include <epicsExport.h>
#include <drvSup.h>
#include <dbCommon.h>
#include <alarm.h>

MksuDriver::MksuDriver(const char *portName, const char *mksuPortName) :
  asynPortDriver(portName, 1, MKSU_NUM_PARAMS,
		 asynInt32Mask | asynInt16ArrayMask | asynInt8ArrayMask | asynDrvUserMask,   // interfaceMask
		 asynInt32Mask | asynInt16ArrayMask | asynInt8ArrayMask, // interruptMask
		 ASYN_CANBLOCK | ASYN_MULTIDEVICE,                       // asynFlags
		 1, 0, 0),           // autoConnect, priority, stackSize
  _mksuPortName(mksuPortName) {
  Log::getInstance() << Log::flagGeneral << Log::dpInfo << Log::showtime << "# Creating MKSU object" << Log::cout;
  for (int i = 0; i < MKSU_NUM_PARAMS; i++) {
    // If the param belons to the Fast ADC block, change the blockId
    // to make it possible to reflesh all waveforms independently
    if (MksuParams[i].blockId == MKSU_FAST_ADC_WF_BLOCK) {
      MksuParams[i].blockId += MksuParams[i].address;
    }
    createParam(MksuParams[i].name.c_str(), MksuParams[i].type, &MksuParams[i].id);
    _paramMap.insert(std::pair<int, MksuParam *>(MksuParams[i].id, &MksuParams[i]));
  }
  _comm = new MksuComm (mksuPortName, &MksuParams[0], MKSU_NUM_PARAMS);
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
asynStatus MksuDriver::readInt8Array(asynUser *pasynUser, epicsInt8 *value, 
				     size_t nElements, size_t *nIn) {
  Log::getInstance() << Log::flagAsyn << Log::dpInfo << Log::showtime;
  Log::getInstance() << "MksuDriver::readInt8Array(reason="
		     << pasynUser->reason
		     << ")" << Log::dp;

  // First find the parameter in the _paramMap using the reason (key) field
  MksuParam *param = getParam(pasynUser->reason);
  if (param == NULL) {
    Log::getInstance() << Log::flagAsyn << Log::dpError << Log::showtime;
    Log::getInstance() << "ERROR: MksuDriver::readInt8Array(...) "
		       << " NULL param for reason " << (int) pasynUser->reason << Log::dp;
    return asynError;
  }

  int status = _comm->refresh(param->blockId);
  if (status != NO_ALARM) {
    Log::getInstance() << Log::flagAsyn << Log::dpError << Log::showtime;
    Log::getInstance() << "ERROR: MksuDriver::readInt8Array(...) "
		       << " MksuComm::refresh() returned " << status << Log::dp;
    return asynError;
  }

  if (_comm->read(param->blockId, param->address, value, param->size)) {
    *nIn = param->size;
    return asynSuccess;
  }
  else {
    Log::getInstance() << Log::flagAsyn << Log::dpError << Log::showtime;
    Log::getInstance() << "ERROR: MksuDriver::readInt8Array(...) "
		       << " MksuComm::read() returned false." << Log::dp; 
   return asynError;
  }
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
asynStatus MksuDriver::readInt16Array(asynUser *pasynUser, epicsInt16 *value,
				      size_t nElements, size_t *nIn) {
  Log::getInstance() << Log::flagAsyn << Log::dpInfo << Log::showtime;
  Log::getInstance() << "MksuDriver::readInt16Array(reason="
		     << pasynUser->reason
		     << ")" << Log::dp;

  // First find the parameter in the _paramMap using the reason (key) field
  MksuParam *param = getParam(pasynUser->reason);
  if (param == NULL) {
    Log::getInstance() << Log::flagAsyn << Log::dpError << Log::showtime;
    Log::getInstance() << "ERROR: MksuDriver::readInt16Array(...) "
		       << " NULL param for reason " << (int) pasynUser->reason << Log::dp;
    return asynError;
  }

  int status = _comm->refresh(param->blockId);
  if (status != NO_ALARM) {
    Log::getInstance() << Log::flagAsyn << Log::dpError << Log::showtime;
    Log::getInstance() << "ERROR: MksuDriver::readInt16Array(...) "
		       << " MksuComm::refresh() returned " << status << Log::dp;
    return asynError;
  }

  if (_comm->read(param->blockId, param->address, value, param->size)) {
    *nIn = param->size;
    /*
    {
      std::ostringstream info;
      
      int offset = 0;
      info << "=== Block " << param->blockId << " ===" << std::endl;
      for (int i = 0; i < 512/32; i++) {
	for (int j = 0; j < 32; j++) {
	  info << std::hex << value[offset] << " ";
	  offset++;
	}
	info << std::endl;
      }
      info << "..." << std::endl;
      
      Log::getInstance() << Log::flagComm << Log::dpWarn
			 << info.str().c_str() << Log::dp;
    }
    */
    if (param->conversion != 0) {
      for (int i = 0; i < param->size; i++) {
	short int sint16 = value[i];
	value[i] = sint16;
      }
    }

    return asynSuccess;
  }
  else {
    Log::getInstance() << Log::flagAsyn << Log::dpError << Log::showtime;
    Log::getInstance() << "ERROR: MksuDriver::readInt16Array(...) "
		       << " MksuComm::read() returned false." << Log::dp;
    return asynError;
  }
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
  Log::getInstance() << Log::flagAsyn << Log::dpInfo << Log::showtime;
  Log::getInstance() << "MksuDriver::readInt32(reason="
		     << pasynUser->reason
		     << ")" << Log::dp;
  // First find the parameter in the _paramMap using the reason (key) field
  MksuParam *param = getParam(pasynUser->reason);
  if (param == NULL) {
    Log::getInstance() << Log::flagAsyn << Log::dpError << Log::showtime;
    Log::getInstance() << "ERROR: MksuDriver::readInt32(...) "
		       << " NULL param for reason " << (int) pasynUser->reason << Log::dp;
    return asynError;
  }

  int status = _comm->refresh(param->blockId);
  if (status != NO_ALARM) {
    Log::getInstance() << Log::flagAsyn << Log::dpError << Log::showtime;
    Log::getInstance() << "ERROR: MksuDriver::readInt32Array(...) "
		       << " MksuComm::refresh() returned " << status << Log::dp;
    return asynError;
  }

  if (_comm->read(param->blockId, param->address, *value)) {
    // Convert from unsigned int16 to signed int16
    if (param->conversion != 0) {
      short int sint16 = *value;
      // TODO: should set the value read back to the paramter library using setIntegerParam()
      // The address of the location to be written is read using getIntegerParam()
      *value = sint16;
    }
    return asynSuccess;
  }
  else {
    Log::getInstance() << Log::flagAsyn << Log::dpError << Log::showtime;
    Log::getInstance() << "ERROR: MksuDriver::readInt32(...) "
		       << " MksuComm::read() returned false." << Log::dp;
    return asynError;
  }
}

/**
 * This method is called when a new value is written to the associated PV,
 * e.g. `caput PV <value>`. The blockId and address of the value in the
 * MKSU memory are first looked up and used by the MksuComm to actually
 * write out the value.
 * 
 * @author L.Piccoli
 */
asynStatus MksuDriver::writeInt32(asynUser *pasynUser, epicsInt32 value) {
  Log::getInstance() << Log::flagAsynWrite << Log::dpInfo << Log::showtime;
  Log::getInstance() << "MksuDriver::writeInt32(reason="
		     << pasynUser->reason << ", value=" << value
		     << ")" << Log::dp;

  // First find the parameter in the _paramMap using the reason (key) field
  MksuParam *param = getParam(pasynUser->reason);
  if (param == NULL) {
    Log::getInstance() << Log::flagAsyn << Log::dpError << Log::showtime;
    Log::getInstance() << "ERROR: MksuDriver::writeInt32(...) "
		       << " NULL param for reason " << (int) pasynUser->reason << Log::dp;
    return asynError;
  }

  if (_comm->write(param->blockId, param->address, value)) {
    // TODO: It seems one has to write the value into the paramLibrary with setIntegerParam()
    return asynSuccess;
  }
  else {
    Log::getInstance() << Log::flagAsyn << Log::dpError << Log::showtime;
    Log::getInstance() << "ERROR: MksuDriver::writeInt32(...) "
		       << " MksuComm::write() returned false." << Log::dp;
    return asynError;
  }
}

/**
 * This method is called when a new value is written to the associated PV,
 * e.g. `caput PV <value>`. The blockId and address of the value in the
 * MKSU memory are first looked up and used by the MksuComm to actually
 * write out the value.
 * 
 * @author L.Piccoli
 */
asynStatus MksuDriver::writeInt16Array(asynUser *pasynUser, epicsInt16 *value,
				       size_t nElements) {

  Log::getInstance() << Log::flagAsynWrite << Log::dpInfo << Log::showtime;
  Log::getInstance() << "MksuDriver::writeInt16Array(reason="
		     << pasynUser->reason << ", value[0]=" << value[0]
		     << ", size=" << (int) nElements << ")" << Log::dp;

  // First find the parameter in the _paramMap using the reason (key) field
  MksuParam *param = getParam(pasynUser->reason);
  if (param == NULL) { 
    Log::getInstance() << Log::flagAsyn << Log::dpError << Log::showtime;
    Log::getInstance() << "ERROR: MksuDriver::writeInt16Array(...) "
		       << " NULL param for reason " << (int) pasynUser->reason << Log::dp;
    return asynError;
  }

  if (_comm->write(param->blockId, param->address, value, param->size)) {
    return asynSuccess;
  }
  else {
    Log::getInstance() << Log::flagAsyn << Log::dpError << Log::showtime;
    Log::getInstance() << "ERROR: MksuDriver::writeInt16Array(...) "
		       << " MksuComm::write() returned false." << Log::dp;
    return asynError;
  }
}

void MksuDriver::report(FILE *fp, int reportDetails) {
  fprintf(fp, "%s: driver report - %s\n",
	  portName, _mksuPortName.c_str());

  std::ostringstream details;

  if (reportDetails > 2) {
    details << "\n================== MKSU Parameters ====================\n";
  
    details << "Name:\t\t\tblockId\taddress\tsize\tid\n";
    
    for (ParamMap::iterator it = _paramMap.begin();
	 it != _paramMap.end(); it++) {
      MksuParam *param = (*it).second;
      details << param->name.c_str() << ":\t";
      if (param->name.length() < 15) {
	details << "\t";
	if (param->name.length() < 7) {
	  details << "\t";
	}
      }
      
      details << param->blockId << "\t"
	      << param->address << "\t"
	      << param->size << "\t"
	      << param->id << "\t";
      if (param->size == 1 && param->blockId > 0x40) {
	epicsInt32 value = -1;
	if (_comm->read(param->blockId, param->address, value)) {
	  details << " latest read: " << value;
	}
      }
      details << std::endl;
    }
    
    details << std::endl;
  }
  _comm->report(details);

  Log::getInstance() << Log::flagGeneral << Log::dpInfo << details.str().c_str() << Log::dp;

  asynPortDriver::report(fp, reportDetails);
}

