// Header file generated from MksuRegister.map on Wed, 07 Dec 2011 00:43:40 +0000

#include <MksuParam.h>
#ifndef MKSUPARAMLIST_H
#define MKSUPARAMLIST_H

// Number of records found in the input file
const int MKSU_NUM_PARAMS = 40;

// Information extracted from the input file
MksuParam MksuParams[MKSU_NUM_PARAMS] = {
  {0x01, asynParamInt32, 0, 1, "STATUS_FADC_SET", -1},
  {0x01, asynParamInt32, 0, 1, "STATUS_CLCKDL_SET", -1},
  {0x01, asynParamInt32, 1, 1, "CTRL_PERMIT_SET", -1},
  {0x01, asynParamInt32, 1, 1, "CTRL_TREN_SET", -1},
  {0x01, asynParamInt32, 1, 1, "CTRL_CFGD_SET", -1},
  {0x01, asynParamInt32, 1, 1, "CTRL_WFTR_SET", -1},
  {0x01, asynParamInt32, 1, 1, "CTRL_AVTR_SET", -1},
  {0x01, asynParamInt32, 2, 1, "CTRL_PERMIT_RSET", -1},
  {0x01, asynParamInt32, 2, 1, "CTRL_TREN_RSET", -1},
  {0x01, asynParamInt32, 2, 1, "CTRL_CFGD_RSET", -1},
  {0x01, asynParamInt32, 2, 1, "CTRL_WFTR_RSET", -1},
  {0x01, asynParamInt32, 2, 1, "CTRL_AVTR_RSET", -1},
  {0x01, asynParamInt32, 3, 1, "MOD_SET", -1},
  {0x41, asynParamInt32, 0, 1, "STATUS", -1},
  {0x41, asynParamInt32, 1, 1, "CTRL", -1},
  {0x41, asynParamInt32, 2, 1, "MOD", -1},
  {0x05, asynParamInt32, 0, 1, "WF_TDLY_DES", -1},
  {0x05, asynParamInt32, 1, 1, "TDLY_DES", -1},
  {0x05, asynParamInt32, 2, 1, "TDLY_RP_DES", -1},
  {0x05, asynParamInt32, 3, 1, "TWTH_RP_DES", -1},
  {0x05, asynParamInt32, 4, 1, "TDLY_FP_DES", -1},
  {0x05, asynParamInt32, 5, 1, "TWTH_FP_DES", -1},
  {0x05, asynParamInt32, 8, 1, "TCNT_IN_DES", -1},
  {0x05, asynParamInt32, 9, 1, "TCNT_OUT_DES", -1},
  {0x45, asynParamInt32, 0, 1, "TDLY_WF", -1},
  {0x45, asynParamInt32, 1, 1, "TDLY", -1},
  {0x45, asynParamInt32, 2, 1, "TDLY_RP", -1},
  {0x45, asynParamInt32, 3, 1, "TWTH_RP", -1},
  {0x45, asynParamInt32, 4, 1, "TDLY_FP", -1},
  {0x45, asynParamInt32, 5, 1, "TWTH_FP", -1},
  {0x45, asynParamInt32, 6, 1, "TDLY_LOC", -1},
  {0x45, asynParamInt32, 7, 1, "TDLY_ACT", -1},
  {0x45, asynParamInt32, 8, 1, "TCNT_IN", -1},
  {0x45, asynParamInt32, 8, 1, "TCNT_OUT", -1},
  {0x64, asynParamInt8Array, 0, 8, "SYS_VERSION", -1},
  {0x64, asynParamInt8Array, 4, 6, "SYS_ID", -1},
  {0x64, asynParamInt8Array, 7, 4, "SYS_SUB_TYPE", -1},
  {0x64, asynParamInt8Array, 9, 8, "SYS_DATE", -1},
  {0x27, asynParamInt16Array, 0, 256, "RF_DRV_SET", -1},
  {0x67, asynParamInt16Array, 0, 256, "RF_DRV", -1},
};

#endif
