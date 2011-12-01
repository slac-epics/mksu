#include "MksuDriver.h"
#include "Log.h"

#include <iocsh.h>
#include <epicsTypes.h>
#include <epicsExport.h>

int createMksu(const char *portName, const char *mksuPortName) {
  try {
    MksuDriver *driver = new MksuDriver(portName, mksuPortName);
    driver = NULL; // Get rid of compiler warning
    return asynSuccess;
  } catch (...) {
    return asynError;
  }
}

extern "C" {

void drvMksu_init(void);

int initMksu(const char *portName, const char *mksuPortName) {
  if (createMksu(portName, mksuPortName) == asynError) {
    printf("####### ERROR: Failed to initialize MKSU #######\n");
  }
  return 0;
}

/* EPICS iocsh shell commands */
static const iocshFuncDef drvMksu_initDef = {"drvMksu_init", 0, 0};
static void drvMksu_initCall(const iocshArgBuf * args) {
	drvMksu_init();
}

static const iocshArg ffLogLevel_Arg0 = {"Flag", iocshArgInt};
static const iocshArg ffLogLevel_Arg1 = {"Level", iocshArgInt};
static const iocshArg * const ffLogLevel_Args[3] = {&ffLogLevel_Arg0, &ffLogLevel_Arg1};
static const iocshFuncDef ffLogLevel_FuncDef = {"ffLogLevel", 2, ffLogLevel_Args};
static const iocshFuncDef ffll_FuncDef = {"ffll", 2, ffLogLevel_Args};

static void LoopLogLevel(const iocshArgBuf *args) {
    int flag = args[0].ival;
    int level = args[1].ival;

    Log::getInstance().setDebugLevel(flag, level);
}

static const iocshArg initArg0 = {"portName", iocshArgString};
static const iocshArg initArg1 = {"mksuPortName", iocshArgString};
static const iocshArg * const initArgs[] = {&initArg0, &initArg1};
static const iocshFuncDef initFuncDef = {"initMksu", 2, initArgs};

static void initCallFunc(const iocshArgBuf *args) {
  initMksu(args[0].sval, args[1].sval);
}

void drvMksu_Register(void) {
  printf("# Registering MKSU iocsh() functions\n");

  iocshRegister(&drvMksu_initDef, drvMksu_initCall);

  iocshRegister(&ffLogLevel_FuncDef, LoopLogLevel);
  iocshRegister(&ffll_FuncDef, LoopLogLevel);

  iocshRegister(&initFuncDef,initCallFunc);
}

void drvMksu_init(void) {
  drvMksu_Register();
}

epicsExportRegistrar(drvMksu_Register);

}
