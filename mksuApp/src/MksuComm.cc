#include <iostream>

#include "MksuComm.h"
#include "Log.h"

MksuComm::MksuComm(std::string mksuPortName) :
  _mksuPortName(mksuPortName) {
}

MksuComm::~MksuComm() {
}

bool MksuComm::read(int blockId, long address, epicsInt32 &value) {
  Log::getInstance() << Log::flagComm << Log::dpInfo;
  Log::getInstance() << "MksuComm::read(blockId="
		     << blockId << ", address=" << address
		     << ")\n" << Log::dp;

  return false;
}

bool MksuComm::write(int blockId, long address, epicsInt32 value) {
  Log::getInstance() << Log::flagComm << Log::dpInfo;
  Log::getInstance() << "MksuComm::write(blockId="
		     << blockId << ", address=" << address
		     << ", value=" << value
		     << ")\n" << Log::dp;
  return false;
}
