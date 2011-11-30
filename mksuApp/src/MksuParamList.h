// Header file generated from MksuRegister.map on Tue, 29 Nov 2011 22:35:07 +0000

#include <MksuParam.h>
#ifndef MKSUPARAMLIST_H
#define MKSUPARAMLIST_H

// Number of records found in the input file
const int MKSU_NUM_PARAMS = 4;

// Information extracted from the input file
MksuParam MksuParams[MKSU_NUM_PARAMS] = {
  {0x05, asynParamInt32, 0, 1, "WF_TRIG_DELAY_WRITE", -1},
  {0x05, asynParamInt32, 1, 1, "MOD_TRIG_DELAY_WRITE", -1},
  {0x45, asynParamInt32, 0, 1, "WF_TRIG_DELAY_READ", -1},
  {0x45, asynParamInt32, 1, 1, "MOD_TRIG_DELAY_READ", -1},
};

#endif
