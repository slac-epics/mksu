// Header file generated from MksuRegister.map on Fri, 02 Dec 2011 00:55:38 +0000

#include <MksuParam.h>
#ifndef MKSUPARAMLIST_H
#define MKSUPARAMLIST_H

// Number of records found in the input file
const int MKSU_NUM_PARAMS = 8;

// Information extracted from the input file
MksuParam MksuParams[MKSU_NUM_PARAMS] = {
  {0x05, asynParamInt32, 0, 1, "WF_TRIG_DELAY_WRITE", -1},
  {0x05, asynParamInt32, 1, 1, "MOD_TRIG_DELAY_WRITE", -1},
  {0x45, asynParamInt32, 0, 1, "WF_TRIG_DELAY_READ", -1},
  {0x45, asynParamInt32, 1, 1, "MOD_TRIG_DELAY_READ", -1},
  {0x64, asynParamInt8Array, 0, 8, "SYS_VERSION", -1},
  {0x64, asynParamInt8Array, 4, 6, "SYS_ID", -1},
  {0x64, asynParamInt8Array, 7, 4, "SYS_SUB_TYPE", -1},
  {0x64, asynParamInt8Array, 9, 8, "SYS_DATE", -1},
};

#endif
