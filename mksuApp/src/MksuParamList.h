// Header file generated from MksuList.map on Mon, 24 Feb 2014 23:51:28 +0000

#include <MksuParam.h>
#ifndef MKSUPARAMLIST_H
#define MKSUPARAMLIST_H

// Number of records found in the input file
const int MKSU_NUM_PARAMS = 422;

// Information extracted from the input file
MksuParam MksuParams[MKSU_NUM_PARAMS] = {
  {0x01, asynParamInt32, 0, 0, 1, "STATUS_FADC_SET", -1},
  {0x01, asynParamInt32, 0, 0, 1, "STATUS_CLCKDL_SET", -1},
  {0x01, asynParamInt32, 1, 0, 1, "CTRL_PERMIT_SET", -1},
  {0x01, asynParamInt32, 1, 0, 1, "CTRL_TREN_SET", -1},
  {0x01, asynParamInt32, 1, 0, 1, "CTRL_CFGD_SET", -1},
  {0x01, asynParamInt32, 1, 0, 1, "CTRL_WFTR_SET", -1},
  {0x01, asynParamInt32, 1, 0, 1, "CTRL_AVTR_SET", -1},
  {0x01, asynParamInt32, 1, 0, 1, "CTRL_SELFTRIG_SET", -1},
  {0x01, asynParamInt32, 1, 0, 1, "CTRL_ACCLSEL_SET", -1},
  {0x01, asynParamInt32, 2, 0, 1, "CTRL_PERMIT_RSET", -1},
  {0x01, asynParamInt32, 2, 0, 1, "CTRL_TREN_RSET", -1},
  {0x01, asynParamInt32, 2, 0, 1, "CTRL_CFGD_RSET", -1},
  {0x01, asynParamInt32, 2, 0, 1, "CTRL_WFTR_RSET", -1},
  {0x01, asynParamInt32, 2, 0, 1, "CTRL_AVTR_RSET", -1},
  {0x01, asynParamInt32, 2, 0, 1, "CTRL_SELFTRIG_RSET", -1},
  {0x01, asynParamInt32, 2, 0, 1, "CTRL_ACCLSEL_RSET", -1},
  {0x01, asynParamInt32, 3, 0, 1, "MOD_SET", -1},
  {0x41, asynParamInt32, 0, 0, 1, "STATUS", -1},
  {0x41, asynParamInt32, 1, 0, 1, "CTRL", -1},
  {0x41, asynParamInt32, 2, 0, 1, "MOD", -1},
  {0x05, asynParamInt32, 0, 0, 1, "WF_TDLY_DES", -1},
  {0x05, asynParamInt32, 1, 0, 1, "TDLY_DES", -1},
  {0x05, asynParamInt32, 2, 0, 1, "TDLY_RP_DES", -1},
  {0x05, asynParamInt32, 3, 0, 1, "TWTH_RP_DES", -1},
  {0x05, asynParamInt32, 4, 0, 1, "TDLY_FP_DES", -1},
  {0x05, asynParamInt32, 5, 0, 1, "TWTH_FP_DES", -1},
  {0x05, asynParamInt32, 10, 0, 1, "RTRIGDIV_DES", -1},
  {0x05, asynParamInt32, 13, 0, 1, "SELF_TDLY_DES", -1},
  {0x45, asynParamInt32, 0, 0, 1, "TDLY_WF", -1},
  {0x45, asynParamInt32, 1, 0, 1, "TDLY", -1},
  {0x45, asynParamInt32, 2, 0, 1, "TDLY_RP", -1},
  {0x45, asynParamInt32, 3, 0, 1, "TWTH_RP", -1},
  {0x45, asynParamInt32, 4, 0, 1, "TDLY_FP", -1},
  {0x45, asynParamInt32, 5, 0, 1, "TWTH_FP", -1},
  {0x45, asynParamInt32, 6, 0, 1, "TDLY_LOC", -1},
  {0x45, asynParamInt32, 7, 0, 1, "TDLY_ACT", -1},
  {0x45, asynParamInt32, 8, 0, 1, "TCNT_IN", -1},
  {0x45, asynParamInt32, 8, 0, 1, "TCNT_OUT", -1},
  {0x45, asynParamInt32, 10, 0, 1, "RTRIGDIV", -1},
  {0x45, asynParamInt32, 11, 0, 1, "LTRIGDIV", -1},
  {0x45, asynParamInt32, 12, 0, 1, "TRIGDIV_ACT", -1},
  {0x45, asynParamInt32, 12, 0, 1, "SELF_TDLY", -1},
  {0x27, asynParamInt16Array, 0, 0, 256, "RF_DRV_WF_SET", -1},
  {0x67, asynParamInt16Array, 0, 0, 256, "RF_DRV_WF", -1},
  {0x64, asynParamInt8Array, 0, 0, 8, "SYS_VERSION", -1},
  {0x64, asynParamInt8Array, 4, 0, 6, "SYS_ID", -1},
  {0x64, asynParamInt8Array, 7, 0, 4, "SYS_SUB_TYPE", -1},
  {0x64, asynParamInt8Array, 9, 0, 8, "SYS_DATE", -1},
  {0x10, asynParamInt32, 0, 0, 1, "STATUS_TOUT_TMO_SET", -1},
  {0x10, asynParamInt32, 0, 0, 1, "STATUS_TIN_TMO_SET", -1},
  {0x10, asynParamInt32, 0, 0, 1, "STATUS_TOUT_OR_SET", -1},
  {0x10, asynParamInt32, 0, 0, 1, "STATUS_TIN_OR_SET", -1},
  {0x10, asynParamInt32, 0, 0, 1, "STATUS_TDELTA_SET", -1},
  {0x10, asynParamInt32, 0, 0, 1, "STATUS_TEMP_CLR", -1},
  {0x10, asynParamInt32, 1, 0, 1, "TOFF_CNTS_SET", -1},
  {0x10, asynParamInt32, 2, 0, 1, "TDELTAMAX_CNTS_SET", -1},
  {0x50, asynParamInt32, 0, 0, 1, "STATUS_TEMP", -1},
  {0x50, asynParamInt32, 1, 1, 1, "TOFF_CNTS", -1},
  {0x50, asynParamInt32, 2, 0, 1, "TDELTAMAX_CNTS", -1},
  {0x50, asynParamInt32, 3, 1, 1, "TDELTA_CNTS", -1},
  {0x50, asynParamInt32, 4, 0, 1, "TOUT_CNTS", -1},
  {0x50, asynParamInt32, 5, 0, 1, "TIN_CNTS", -1},
  {0x63, asynParamInt32, 0, 0, 1, "XTEMP_RAW", -1},
  {0x63, asynParamInt32, 1, 0, 1, "XV_INT_RAW", -1},
  {0x63, asynParamInt32, 2, 0, 1, "XV_AUX_RAW", -1},
  {0x63, asynParamInt32, 3, 0, 1, "XTEMP_MAX_RAW", -1},
  {0x63, asynParamInt32, 4, 0, 1, "XV_MAX_INT_RAW", -1},
  {0x63, asynParamInt32, 5, 0, 1, "XV_MAX_AUX_RAW", -1},
  {0x63, asynParamInt32, 6, 0, 1, "XTEMP_MIN_RAW", -1},
  {0x63, asynParamInt32, 7, 0, 1, "XV_MIN_INT_RAW", -1},
  {0x63, asynParamInt32, 8, 0, 1, "XV_MIN_AUX_RAW", -1},
  {0x14, asynParamInt32, 0, 0, 1, "STATUS_MGNT_BRKR_CLR_SET", -1},
  {0x14, asynParamInt32, 0, 0, 1, "STATUS_MGNT_CURR_CLR_SET", -1},
  {0x14, asynParamInt32, 0, 0, 1, "STATUS_MGNT_CILK_CLR_SET", -1},
  {0x14, asynParamInt32, 0, 0, 1, "FG_MGNT_CLR", -1},
  {0x14, asynParamInt32, 3, 0, 1, "FG_MGNT_TST_SET_CLR", -1},
  {0x14, asynParamInt32, 4, 0, 1, "FG_MGNT_TST_RESET_CLR", -1},
  {0x14, asynParamInt32, 3, 0, 1, "CTRL_MGNT_BRKR_TST_SET", -1},
  {0x14, asynParamInt32, 3, 0, 1, "CTRL_MGNT_CURR_TST_SET", -1},
  {0x14, asynParamInt32, 3, 0, 1, "CTRL_MGNT_CILK_TST_SET", -1},
  {0x14, asynParamInt32, 4, 0, 1, "CTRL_MGNT_BRKR_TST_RESET", -1},
  {0x14, asynParamInt32, 4, 0, 1, "CTRL_MGNT_CURR_TST_RESET", -1},
  {0x14, asynParamInt32, 4, 0, 1, "CTRL_MGNT_CILK_TST_RESET", -1},
  {0x54, asynParamInt32, 0, 0, 1, "MGNT_STATUS", -1},
  {0x54, asynParamInt32, 2, 0, 1, "MGNT_TEST", -1},
  {0x04, asynParamInt32, 0, 0, 1, "STATUS_BV_LO_SET", -1},
  {0x04, asynParamInt32, 0, 0, 1, "STATUS_BV_HI_SET", -1},
  {0x04, asynParamInt32, 0, 0, 1, "STATUS_BC_LO_SET", -1},
  {0x04, asynParamInt32, 0, 0, 1, "STATUS_BC_HI_SET", -1},
  {0x04, asynParamInt32, 0, 0, 1, "STATUS_FP_LO_SET", -1},
  {0x04, asynParamInt32, 0, 0, 1, "STATUS_FP_HI_SET", -1},
  {0x04, asynParamInt32, 0, 0, 1, "STATUS_RP_LO_SET", -1},
  {0x04, asynParamInt32, 0, 0, 1, "STATUS_RP_HI_SET", -1},
  {0x04, asynParamInt32, 0, 0, 1, "STATUS_BC_LO10S_SET", -1},
  {0x04, asynParamInt32, 0, 0, 1, "STATUS_FADC_CLR", -1},
  {0x04, asynParamInt32, 1, 0, 1, "BV_LO_SET", -1},
  {0x04, asynParamInt32, 2, 0, 1, "BV_HI_SET", -1},
  {0x04, asynParamInt32, 3, 0, 1, "BV_AVG_STA_SET", -1},
  {0x04, asynParamInt32, 4, 0, 1, "BV_AVG_END_SET", -1},
  {0x04, asynParamInt32, 5, 0, 1, "BC_LO_SET", -1},
  {0x04, asynParamInt32, 6, 0, 1, "BC_HI_SET", -1},
  {0x04, asynParamInt32, 7, 0, 1, "BC_AVG_STA_SET", -1},
  {0x04, asynParamInt32, 8, 0, 1, "BC_AVG_END_SET", -1},
  {0x04, asynParamInt32, 9, 0, 1, "FP_LO_SET", -1},
  {0x04, asynParamInt32, 10, 0, 1, "FP_HI_SET", -1},
  {0x04, asynParamInt32, 11, 0, 1, "FP_AVG_STA_SET", -1},
  {0x04, asynParamInt32, 12, 0, 1, "FP_AVG_END_SET", -1},
  {0x04, asynParamInt32, 13, 0, 1, "RP_LO_SET", -1},
  {0x04, asynParamInt32, 14, 0, 1, "RP_HI_SET", -1},
  {0x04, asynParamInt32, 15, 0, 1, "RP_AVG_STA_SET", -1},
  {0x04, asynParamInt32, 16, 0, 1, "RP_AVG_END_SET", -1},
  {0x04, asynParamInt32, 17, 0, 1, "WF_CNT_SET", -1},
  {0x44, asynParamInt32, 0, 0, 1, "STATUS_FADC", -1},
  {0x44, asynParamInt32, 1, 1, 1, "BV_LO", -1},
  {0x70, asynParamInt16Array, 0, 1, 2, "BV_LO_PLOT", -1},
  {0x44, asynParamInt32, 2, 1, 1, "BV_HI", -1},
  {0x70, asynParamInt16Array, 2, 1, 2, "BV_HI_PLOT", -1},
  {0x44, asynParamInt32, 3, 0, 1, "BV_AVG_STA", -1},
  {0x70, asynParamInt16Array, 4, 1, 2, "BV_STA_PLOT", -1},
  {0x44, asynParamInt32, 4, 0, 1, "BV_AVG_END", -1},
  {0x70, asynParamInt16Array, 6, 1, 2, "BV_END_PLOT", -1},
  {0x44, asynParamInt32, 5, 1, 1, "BC_LO", -1},
  {0x70, asynParamInt16Array, 8, 1, 2, "BC_LO_PLOT", -1},
  {0x44, asynParamInt32, 6, 1, 1, "BC_HI", -1},
  {0x70, asynParamInt16Array, 10, 1, 2, "BC_HI_PLOT", -1},
  {0x44, asynParamInt32, 7, 0, 1, "BC_AVG_STA", -1},
  {0x70, asynParamInt16Array, 12, 1, 2, "BC_STA_PLOT", -1},
  {0x44, asynParamInt32, 8, 0, 1, "BC_AVG_END", -1},
  {0x70, asynParamInt16Array, 14, 1, 2, "BC_END_PLOT", -1},
  {0x44, asynParamInt32, 9, 1, 1, "FP_LO", -1},
  {0x70, asynParamInt16Array, 16, 1, 2, "FP_LO_PLOT", -1},
  {0x44, asynParamInt32, 10, 1, 1, "FP_HI", -1},
  {0x70, asynParamInt16Array, 18, 1, 2, "FP_HI_PLOT", -1},
  {0x44, asynParamInt32, 11, 0, 1, "FP_AVG_STA", -1},
  {0x70, asynParamInt16Array, 20, 1, 2, "FP_STA_PLOT", -1},
  {0x44, asynParamInt32, 12, 0, 1, "FP_AVG_END", -1},
  {0x70, asynParamInt16Array, 22, 1, 2, "FP_END_PLOT", -1},
  {0x44, asynParamInt32, 13, 1, 1, "RP_LO", -1},
  {0x70, asynParamInt16Array, 24, 1, 2, "RP_LO_PLOT", -1},
  {0x44, asynParamInt32, 14, 1, 1, "RP_HI", -1},
  {0x70, asynParamInt16Array, 26, 1, 2, "RP_HI_PLOT", -1},
  {0x44, asynParamInt32, 15, 0, 1, "RP_AVG_STA", -1},
  {0x70, asynParamInt16Array, 28, 1, 2, "RP_STA_PLOT", -1},
  {0x44, asynParamInt32, 16, 0, 1, "RP_AVG_END", -1},
  {0x70, asynParamInt16Array, 30, 1, 2, "RP_END_PLOT", -1},
  {0x44, asynParamInt32, 17, 0, 1, "WF_CNT", -1},
  {0x44, asynParamInt32, 18, 1, 1, "BV_AVG", -1},
  {0x44, asynParamInt32, 19, 1, 1, "BC_AVG", -1},
  {0x44, asynParamInt32, 20, 1, 1, "FP_AVG", -1},
  {0x44, asynParamInt32, 21, 1, 1, "RP_AVG", -1},
  {0x44, asynParamInt32, 22, 1, 1, "BV", -1},
  {0x44, asynParamInt32, 23, 1, 1, "BC", -1},
  {0x44, asynParamInt32, 24, 1, 1, "FP", -1},
  {0x44, asynParamInt32, 25, 1, 1, "RP", -1},
  {0x61, asynParamInt16Array, 0, 1, 512, "BV_WF", -1},
  {0x61, asynParamInt16Array, 512, 1, 512, "BC_WF", -1},
  {0x61, asynParamInt16Array, 1024, 1, 512, "FP_WF", -1},
  {0x61, asynParamInt16Array, 1536, 1, 512, "RP_WF", -1},
  {0x61, asynParamInt16Array, 2048, 1, 512, "BV_AVG_WF", -1},
  {0x61, asynParamInt16Array, 2560, 1, 512, "BC_AVG_WF", -1},
  {0x61, asynParamInt16Array, 3072, 1, 512, "FP_AVG_WF", -1},
  {0x61, asynParamInt16Array, 3584, 1, 512, "RP_AVG_WF", -1},
  {0x06, asynParamInt32, 0, 0, 1, "STATUS_RF_3O5_SET", -1},
  {0x06, asynParamInt32, 0, 0, 1, "STATUS_RF_BC_LO_SET", -1},
  {0x06, asynParamInt32, 0, 0, 1, "RF_STATUS_CLR", -1},
  {0x06, asynParamInt32, 1, 0, 1, "CTRL_RF_RAMP_SLOW", -1},
  {0x06, asynParamInt32, 1, 0, 1, "CTRL_BYPASS_SET", -1},
  {0x06, asynParamInt32, 2, 0, 1, "CTRL_RF_RAMP_NORM", -1},
  {0x06, asynParamInt32, 2, 0, 1, "CTRL_BYPASS_RESET", -1},
  {0x06, asynParamInt32, 3, 0, 1, "RF_RDRV_SET", -1},
  {0x46, asynParamInt32, 0, 0, 1, "RF_STATUS", -1},
  {0x46, asynParamInt32, 1, 0, 1, "RF_CTRL", -1},
  {0x46, asynParamInt32, 2, 1, 1, "RF_RDRV", -1},
  {0x46, asynParamInt32, 3, 1, 1, "RF_LDRV", -1},
  {0x46, asynParamInt32, 4, 1, 1, "RF_DRV", -1},
  {0x46, asynParamInt32, 5, 1, 1, "RF_ACTDRV", -1},
  {0x08, asynParamInt32, 0, 0, 1, "STATUS_TANKPUMP_PUMPII_CLR_SET", -1},
  {0x08, asynParamInt32, 0, 0, 1, "STATUS_TANKPUMP_TANKHI_CLR_SET", -1},
  {0x08, asynParamInt32, 0, 0, 1, "STATUS_TANKPUMP_TANKLO_CLR_SET", -1},
  {0x08, asynParamInt32, 0, 0, 1, "FG_TANKPUMP_CLR", -1},
  {0x08, asynParamInt32, 1, 0, 1, "FG_TANKPUMP_CTRL_SET_CLR", -1},
  {0x08, asynParamInt32, 2, 0, 1, "FG_TANKPUMP_CTRL_RESET_CLR", -1},
  {0x08, asynParamInt32, 3, 0, 1, "FG_TANKPUMP_TST_SET_CLR", -1},
  {0x08, asynParamInt32, 4, 0, 1, "FG_TANKPUMP_TST_RESET_CLR", -1},
  {0x08, asynParamInt32, 3, 0, 1, "CTRL_TANKPUMP_PUMPII_TST_SET", -1},
  {0x08, asynParamInt32, 3, 0, 1, "CTRL_TANKPUMP_TANKHI_TST_SET", -1},
  {0x08, asynParamInt32, 3, 0, 1, "CTRL_TANKPUMP_TANKLO_TST_SET", -1},
  {0x08, asynParamInt32, 4, 0, 1, "CTRL_TANKPUMP_PUMPII_TST_RESET", -1},
  {0x08, asynParamInt32, 4, 0, 1, "CTRL_TANKPUMP_TANKHI_TST_RESET", -1},
  {0x08, asynParamInt32, 4, 0, 1, "CTRL_TANKPUMP_TANKLO_TST_RESET", -1},
  {0x08, asynParamInt32, 1, 0, 1, "CTRL_TANKPUMP_PUMPII_CTRL_SET", -1},
  {0x08, asynParamInt32, 1, 0, 1, "CTRL_TANKPUMP_TANKHI_CTRL_SET", -1},
  {0x08, asynParamInt32, 1, 0, 1, "CTRL_TANKPUMP_TANKLO_CTRL_SET", -1},
  {0x08, asynParamInt32, 2, 0, 1, "CTRL_TANKPUMP_PUMPII_CTRL_RESET", -1},
  {0x08, asynParamInt32, 2, 0, 1, "CTRL_TANKPUMP_TANKHI_CTRL_RESET", -1},
  {0x08, asynParamInt32, 2, 0, 1, "CTRL_TANKPUMP_TANKLO_CTRL_RESET", -1},
  {0x48, asynParamInt32, 0, 0, 1, "TANKPUMP_STATUS", -1},
  {0x48, asynParamInt32, 1, 0, 1, "TANKPUMP_CONTROL", -1},
  {0x48, asynParamInt32, 2, 0, 1, "TANKPUMP_TEST", -1},
  {0x0A, asynParamInt32, 1, 0, 1, "CTRL_MOD_CPWR_SET", -1},
  {0x0A, asynParamInt32, 1, 0, 1, "CTRL_HVON_SET", -1},
  {0x0A, asynParamInt32, 1, 0, 1, "CTRL_HVOFF_SET", -1},
  {0x0A, asynParamInt32, 1, 0, 1, "CTRL_FLTRST_SET", -1},
  {0x0A, asynParamInt32, 3, 0, 1, "CTRL_MOD_HVON_TST_SET", -1},
  {0x0A, asynParamInt32, 3, 0, 1, "CTRL_MOD_FLK_TST_SET", -1},
  {0x0A, asynParamInt32, 3, 0, 1, "CTRL_MOD_EILK_TST_SET", -1},
  {0x0A, asynParamInt32, 3, 0, 1, "CTRL_MOD_HVOC_TST_SET", -1},
  {0x0A, asynParamInt32, 3, 0, 1, "CTRL_MOD_EOLC_TST_SET", -1},
  {0x0A, asynParamInt32, 3, 0, 1, "CTRL_MOD_TTOC_TST_SET", -1},
  {0x0A, asynParamInt32, 3, 0, 1, "CTRL_MOD_HVRDY_TST_SET", -1},
  {0x0A, asynParamInt32, 3, 0, 1, "CTRL_MOD_AVAIL_TST_SET", -1},
  {0x0A, asynParamInt32, 3, 0, 1, "CTRL_MOD_ILKC_TST_SET", -1},
  {0x0A, asynParamInt32, 3, 0, 1, "CTRL_MOD_CTRL_PFLT_TST_SET", -1},
  {0x0A, asynParamInt32, 3, 0, 1, "CTRL_MOD_KFTDLY_TST_SET", -1},
  {0x0A, asynParamInt32, 3, 0, 1, "CTRL_MOD_VVS_TST_SET", -1},
  {0x0A, asynParamInt32, 4, 0, 1, "CTRL_MOD_HVON_TST_RESET", -1},
  {0x0A, asynParamInt32, 4, 0, 1, "CTRL_MOD_FLK_TST_RESET", -1},
  {0x0A, asynParamInt32, 4, 0, 1, "CTRL_MOD_EILK_TST_RESET", -1},
  {0x0A, asynParamInt32, 4, 0, 1, "CTRL_MOD_HVOC_TST_RESET", -1},
  {0x0A, asynParamInt32, 4, 0, 1, "CTRL_MOD_EOLC_TST_RESET", -1},
  {0x0A, asynParamInt32, 4, 0, 1, "CTRL_MOD_TTOC_TST_RESET", -1},
  {0x0A, asynParamInt32, 4, 0, 1, "CTRL_MOD_HVRDY_TST_RESET", -1},
  {0x0A, asynParamInt32, 4, 0, 1, "CTRL_MOD_AVAIL_TST_RESET", -1},
  {0x0A, asynParamInt32, 4, 0, 1, "CTRL_MOD_ILKC_TST_RESET", -1},
  {0x0A, asynParamInt32, 4, 0, 1, "CTRL_MOD_CTRL_PFLT_TST_RESET", -1},
  {0x0A, asynParamInt32, 4, 0, 1, "CTRL_MOD_KFTDLY_TST_RESET", -1},
  {0x0A, asynParamInt32, 4, 0, 1, "CTRL_MOD_VVS_TST_RESET", -1},
  {0x4A, asynParamInt32, 0, 0, 1, "MOD_STATUS", -1},
  {0x4A, asynParamInt32, 1, 0, 1, "MOD_CTRL", -1},
  {0x4A, asynParamInt32, 2, 0, 1, "MOD_TEST", -1},
  {0x0B, asynParamInt32, 0, 0, 1, "STATUS_WATR_KLY_CLR_SET", -1},
  {0x0B, asynParamInt32, 0, 0, 1, "STATUS_WATR_WG1_CLR_SET", -1},
  {0x0B, asynParamInt32, 0, 0, 1, "STATUS_WATR_WG2_CLR_SET", -1},
  {0x0B, asynParamInt32, 0, 0, 1, "STATUS_WATR_ACC1_CLR_SET", -1},
  {0x0B, asynParamInt32, 0, 0, 1, "STATUS_WATR_ACC2_CLR_SET", -1},
  {0x0B, asynParamInt32, 0, 0, 1, "STATUS_WATR_FLOW_CLR_SET", -1},
  {0x0B, asynParamInt32, 0, 0, 1, "STATUS_WATR_FLT_CLR_SET", -1},
  {0x0B, asynParamInt32, 0, 0, 1, "STATUS_WATR_KLY_DB_CLR_SET", -1},
  {0x0B, asynParamInt32, 0, 0, 1, "STATUS_WATR_WG1_DB_CLR_SET", -1},
  {0x0B, asynParamInt32, 0, 0, 1, "STATUS_WATR_WG2_DB_CLR_SET", -1},
  {0x0B, asynParamInt32, 0, 0, 1, "STATUS_WATR_ACC1_DB_CLR_SET", -1},
  {0x0B, asynParamInt32, 0, 0, 1, "STATUS_WATR_ACC2_DB_CLR_SET", -1},
  {0x0B, asynParamInt32, 0, 0, 1, "FG_WATR_CLR", -1},
  {0x0B, asynParamInt32, 3, 0, 1, "FG_WATR_TST_SET_CLR", -1},
  {0x0B, asynParamInt32, 4, 0, 1, "FG_WATR_TST_RESET_CLR", -1},
  {0x0B, asynParamInt32, 3, 0, 1, "CTRL_WATR_KLY_TST_SET", -1},
  {0x0B, asynParamInt32, 3, 0, 1, "CTRL_WATR_WG1_TST_SET", -1},
  {0x0B, asynParamInt32, 3, 0, 1, "CTRL_WATR_WG2_TST_SET", -1},
  {0x0B, asynParamInt32, 3, 0, 1, "CTRL_WATR_ACC1_TST_SET", -1},
  {0x0B, asynParamInt32, 3, 0, 1, "CTRL_WATR_ACC2_TST_SET", -1},
  {0x0B, asynParamInt32, 4, 0, 1, "CTRL_WATR_TST_RESET", -1},
  {0x0B, asynParamInt32, 4, 0, 1, "CTRL_WATR_WG1_TST_RESET", -1},
  {0x0B, asynParamInt32, 4, 0, 1, "CTRL_WATR_WG2_TST_RESET", -1},
  {0x0B, asynParamInt32, 4, 0, 1, "CTRL_WATR_ACC1_TST_RESET", -1},
  {0x0B, asynParamInt32, 4, 0, 1, "CTRL_WATR_ACC2_TST_RESET", -1},
  {0x4B, asynParamInt32, 0, 0, 1, "WATR_STATUS", -1},
  {0x4B, asynParamInt32, 2, 0, 1, "WATR_TEST", -1},
  {0x11, asynParamInt32, 3, 0, 1, "CTRL_LMOD_AVAIL_TST_SET", -1},
  {0x11, asynParamInt32, 3, 0, 1, "CTRL_LMOD_WGV_TST_SET", -1},
  {0x11, asynParamInt32, 3, 0, 1, "CTRL_LMOD_WGTC_TST_SET", -1},
  {0x11, asynParamInt32, 4, 0, 1, "CTRL_LMOD_AVAIL_TST_RESET", -1},
  {0x11, asynParamInt32, 4, 0, 1, "CTRL_LMOD_WGV_TST_RESET", -1},
  {0x11, asynParamInt32, 4, 0, 1, "CTRL_LMOD_WGTC_TST_RESET", -1},
  {0x51, asynParamInt32, 0, 0, 1, "LMOD_STATUS", -1},
  {0x51, asynParamInt32, 2, 0, 1, "LMOD_TEST", -1},
  {0x12, asynParamInt32, 3, 0, 1, "CTRL_VPIO_TST_SET", -1},
  {0x12, asynParamInt32, 4, 0, 1, "CTRL_VPIO_TST_RESET", -1},
  {0x52, asynParamInt32, 0, 0, 1, "VPIO_STATUS", -1},
  {0x52, asynParamInt32, 2, 0, 1, "VPIO_TEST", -1},
  {0x13, asynParamInt32, 0, 0, 1, "STATUS_WGV_OK_CLR_SET", -1},
  {0x13, asynParamInt32, 0, 0, 1, "STATUS_WGV_BAD_CLR_SET", -1},
  {0x13, asynParamInt32, 0, 0, 1, "FG_WGV_CLR", -1},
  {0x13, asynParamInt32, 3, 0, 1, "FG_WGV_TST_SET_CLR", -1},
  {0x13, asynParamInt32, 4, 0, 1, "FG_WGV_TST_RESET_CLR", -1},
  {0x13, asynParamInt32, 3, 0, 1, "CTRL_WGV_OK_TST_SET", -1},
  {0x13, asynParamInt32, 3, 0, 1, "CTRL_WGV_BAD_TST_SET", -1},
  {0x13, asynParamInt32, 4, 0, 1, "CTRL_WGV_OK_TST_RESET", -1},
  {0x13, asynParamInt32, 4, 0, 1, "CTRL_WGV_BAD_TST_RESET", -1},
  {0x53, asynParamInt32, 0, 0, 1, "WGV_STATUS", -1},
  {0x53, asynParamInt32, 2, 0, 1, "WGV_TEST", -1},
  {0x03, asynParamInt32, 0, 0, 1, "STATUS_KVAC_LO_SET", -1},
  {0x03, asynParamInt32, 0, 0, 1, "STATUS_KVAC_HI_SET", -1},
  {0x03, asynParamInt32, 0, 0, 1, "STATUS_WVAC_LO_SET", -1},
  {0x03, asynParamInt32, 0, 0, 1, "STATUS_WVAC_HI_SET", -1},
  {0x03, asynParamInt32, 0, 0, 1, "STATUS_FC_LO_SET", -1},
  {0x03, asynParamInt32, 0, 0, 1, "STATUS_FC_HI_SET", -1},
  {0x03, asynParamInt32, 0, 0, 1, "STATUS_FCG_LO_SET", -1},
  {0x03, asynParamInt32, 0, 0, 1, "STATUS_FCG_HI_SET", -1},
  {0x03, asynParamInt32, 0, 0, 1, "STATUS_SLOW_CLR", -1},
  {0x03, asynParamInt32, 1, 0, 1, "KVAC_LO_SET", -1},
  {0x03, asynParamInt32, 2, 0, 1, "KVAC_HI_SET", -1},
  {0x03, asynParamInt32, 3, 0, 1, "WVAC_LO_SET", -1},
  {0x03, asynParamInt32, 4, 0, 1, "WVAC_HI_SET", -1},
  {0x03, asynParamInt32, 5, 0, 1, "FC_LO_SET", -1},
  {0x03, asynParamInt32, 6, 0, 1, "FC_HI_SET", -1},
  {0x03, asynParamInt32, 7, 0, 1, "FCG_LO_SET", -1},
  {0x03, asynParamInt32, 8, 0, 1, "FCG_HI_SET", -1},
  {0x43, asynParamInt32, 0, 0, 1, "STATUS_SLOW", -1},
  {0x43, asynParamInt32, 1, 1, 1, "KVAC_LO", -1},
  {0x43, asynParamInt32, 2, 1, 1, "KVAC_HI", -1},
  {0x43, asynParamInt32, 3, 1, 1, "WVAC_LO", -1},
  {0x43, asynParamInt32, 4, 1, 1, "WVAC_HI", -1},
  {0x43, asynParamInt32, 5, 1, 1, "FC_LO", -1},
  {0x43, asynParamInt32, 6, 1, 1, "FC_HI", -1},
  {0x43, asynParamInt32, 7, 1, 1, "FCG_LO", -1},
  {0x43, asynParamInt32, 8, 1, 1, "FCG_HI", -1},
  {0x43, asynParamInt32, 9, 1, 1, "KVAC_AVG", -1},
  {0x43, asynParamInt32, 10, 1, 1, "WVAC_AVG", -1},
  {0x43, asynParamInt32, 11, 1, 1, "FC_AVG", -1},
  {0x43, asynParamInt32, 12, 1, 1, "FCG_AVG", -1},
  {0x62, asynParamInt32, 0, 1, 1, "MK_N24_RAW", -1},
  {0x62, asynParamInt32, 1, 1, 1, "MK_N15_RAW", -1},
  {0x62, asynParamInt32, 2, 1, 1, "MK_N5_RAW", -1},
  {0x62, asynParamInt32, 3, 0, 1, "MK_P2D5_RAW", -1},
  {0x62, asynParamInt32, 4, 0, 1, "MK_P3D3_RAW", -1},
  {0x62, asynParamInt32, 5, 0, 1, "MK_P5_RAW", -1},
  {0x62, asynParamInt32, 6, 0, 1, "MK_P15_RAW", -1},
  {0x62, asynParamInt32, 7, 0, 1, "MK_P24_RAW", -1},
  {0x07, asynParamInt32, 0, 0, 1, "FC_DAC_SET", -1},
  {0x47, asynParamInt32, 0, 0, 1, "FC_DAC", -1},
  {0x09, asynParamInt32, 0, 0, 1, "STATUS_FG_RFOFF_CLR_SET", -1},
  {0x09, asynParamInt32, 0, 0, 1, "STATUS_FG_MGNTOFF_CLR_SET", -1},
  {0x09, asynParamInt32, 0, 0, 1, "STATUS_FG_EILKOPN_CLR_SET", -1},
  {0x09, asynParamInt32, 0, 0, 1, "STATUS_FG_HVOFF_CLR_SET", -1},
  {0x09, asynParamInt32, 0, 0, 1, "STATUS_FG_TRIGDIS_CLR_SET", -1},
  {0x09, asynParamInt32, 0, 0, 1, "STATUS_FG_FPTRIGEN_CLR_SET", -1},
  {0x09, asynParamInt32, 0, 0, 1, "STATUS_FG_BCLOW_CLR_SET", -1},
  {0x09, asynParamInt32, 0, 0, 1, "FG_STATUS_CLR", -1},
  {0x09, asynParamInt32, 1, 0, 1, "FG_CNT_CLR", -1},
  {0x09, asynParamInt32, 2, 0, 1, "FG_BYPASS0_SET_CLR", -1},
  {0x09, asynParamInt32, 3, 0, 1, "FG_BYPASS1_SET_CLR", -1},
  {0x09, asynParamInt32, 4, 0, 1, "FG_BYPASS0_RESET_CLR", -1},
  {0x09, asynParamInt32, 5, 0, 1, "FG_BYPASS1_RESET_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "FG_FAULT0_RESET_CLR", -1},
  {0x09, asynParamInt32, 7, 0, 1, "FG_FAULT1_RESET_CLR", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_FG_PUMPII_BP_SET", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_TANKHI_BP_SET", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_TANKLO_BP_SET", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_MGNTBRKR_BP_SET", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_MGNTCNOK_BP_SET", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_MGNTCILK_BP_SET", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_WVACBAD_BP_SET", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_WVACNOK_BP_SET", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_KVACFLT_BP_SET", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_WGVFLT_BP_SET", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_WGTCFLT_BP_SET", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_KLYSFSOPEN_BP_SET", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_WGFLW2_BP_SET", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_WGFLW1_BP_SET", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_ACCFLW2_BP_SET", -1},
  {0x09, asynParamInt32, 2, 0, 1, "CTRL_ACCFLW1_BP_SET", -1},
  {0x09, asynParamInt32, 3, 0, 1, "CTRL_FG_RPOT_BP_SET", -1},
  {0x09, asynParamInt32, 3, 0, 1, "CTRL_FG_FPOT_BP_SET", -1},
  {0x09, asynParamInt32, 3, 0, 1, "CTRL_FG_BVOT_BP_SET", -1},
  {0x09, asynParamInt32, 3, 0, 1, "CTRL_FG_BCOT_BP_SET", -1},
  {0x09, asynParamInt32, 3, 0, 1, "CTRL_FG_FCGCURR_BP_SET", -1},
  {0x09, asynParamInt32, 3, 0, 1, "CTRL_FG_FCCURR_BP_SET", -1},
  {0x09, asynParamInt32, 3, 0, 1, "CTRL_FG_WVAC_BP_SET", -1},
  {0x09, asynParamInt32, 3, 0, 1, "CTRL_FG_KVAC_BP_SET", -1},
  {0x09, asynParamInt32, 3, 0, 1, "CTRL_FG_KTEMPDIFF_BP_SET", -1},
  {0x09, asynParamInt32, 3, 0, 1, "CTRL_FG_24VLOW_BP_SET", -1},
  {0x09, asynParamInt32, 3, 0, 1, "CTRL_FG_BEAMLOW_BP_SET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_FG_PUMPII_BP_RESET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_TANKHI_BP_RESET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_TANKLO_BP_RESET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_MGNTBRKR_BP_RESET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_MGNTCNOK_BP_RESET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_MGNTCILK_BP_RESET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_WVACBAD_BP_RESET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_WVACNOK_BP_RESET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_KVACFLT_BP_RESET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_WGVFLT_BP_RESET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_WGTCFLT_BP_RESET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_KLYSFSOPEN_BP_RESET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_WGFLW2_BP_RESET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_WGFLW1_BP_RESET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_ACCFLW2_BP_RESET", -1},
  {0x09, asynParamInt32, 4, 0, 1, "CTRL_ACCFLW1_BP_RESET", -1},
  {0x09, asynParamInt32, 5, 0, 1, "CTRL_FG_RPOT_BP_RESET", -1},
  {0x09, asynParamInt32, 5, 0, 1, "CTRL_FG_FPOT_BP_RESET", -1},
  {0x09, asynParamInt32, 5, 0, 1, "CTRL_FG_BVOT_BP_RESET", -1},
  {0x09, asynParamInt32, 5, 0, 1, "CTRL_FG_BCOT_BP_RESET", -1},
  {0x09, asynParamInt32, 5, 0, 1, "CTRL_FG_FCGCURR_BP_RESET", -1},
  {0x09, asynParamInt32, 5, 0, 1, "CTRL_FG_FCCURR_BP_RESET", -1},
  {0x09, asynParamInt32, 5, 0, 1, "CTRL_FG_WVAC_BP_RESET", -1},
  {0x09, asynParamInt32, 5, 0, 1, "CTRL_FG_KVAC_BP_RESET", -1},
  {0x09, asynParamInt32, 5, 0, 1, "CTRL_FG_KTEMPDIFF_BP_RESET", -1},
  {0x09, asynParamInt32, 5, 0, 1, "CTRL_FG_24VLOW_BP_RESET", -1},
  {0x09, asynParamInt32, 5, 0, 1, "CTRL_FG_BEAMLOW_BP_RESET", -1},
  {0x49, asynParamInt32, 0, 0, 1, "FG_STATUS", -1},
  {0x49, asynParamInt32, 1, 0, 1, "FG_FLT_CNT", -1},
  {0x49, asynParamInt32, 2, 0, 1, "FG_BYPASS0", -1},
  {0x49, asynParamInt32, 3, 0, 1, "FG_BYPASS1", -1},
  {0x49, asynParamInt32, 4, 0, 1, "FG_FAULT0", -1},
  {0x49, asynParamInt32, 5, 0, 1, "FG_FAULT1", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_FG_PUMPII_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_TANKHI_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_TANKLO_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_MGNTBRKR_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_MGNTCNOK_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_MGNTCILK_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_WVACBAD_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_WVACNOK_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_KVACFLT_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_WGVFLT_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_WGTCFLT_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_KLYSFSOPEN_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_WGFLW2_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_WGFLW1_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_ACCFLW2_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 6, 0, 1, "CTRL_ACCFLW1_FAULT0_CLR", -1},
  {0x09, asynParamInt32, 7, 0, 1, "CTRL_FG_RPOT_FAULT1_CLR", -1},
  {0x09, asynParamInt32, 7, 0, 1, "CTRL_FG_FPOT_FAULT1_CLR", -1},
  {0x09, asynParamInt32, 7, 0, 1, "CTRL_FG_BVOT_FAULT1_CLR", -1},
  {0x09, asynParamInt32, 7, 0, 1, "CTRL_FG_BCOT_FAULT1_CLR", -1},
  {0x09, asynParamInt32, 7, 0, 1, "CTRL_FG_FCGCURR_FAULT1_CLR", -1},
  {0x09, asynParamInt32, 7, 0, 1, "CTRL_FG_FCCURR_FAULT1_CLR", -1},
  {0x09, asynParamInt32, 7, 0, 1, "CTRL_FG_WVAC_FAULT1_CLR", -1},
  {0x09, asynParamInt32, 7, 0, 1, "CTRL_FG_KVAC_FAULT1_CLR", -1},
  {0x09, asynParamInt32, 7, 0, 1, "CTRL_FG_KTEMPDIFF_FAULT1_CLR", -1},
  {0x09, asynParamInt32, 7, 0, 1, "CTRL_FG_24VLOW_FAULT1_CLR", -1},
  {0x09, asynParamInt32, 7, 0, 1, "CTRL_FG_BEAMLOW_FAULT1_CLR", -1},
};

#endif
