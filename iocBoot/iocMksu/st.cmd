#! ../../bin/linux-x86/example

dbLoadDatabase("../../dbd/example.dbd")
example_registerRecordDeviceDriver(pdbbase)

drvMksu_init()
drvAsynIPPortConfigure("MksuServer", "134.79.218.64:56789 UDP", 0, 0, 1)
#drvAsynIPPortConfigure("MksuServer", "192.168.0.21:56789 UDP", 0, 0, 1)
#drvAsynIPPortConfigure("MksuServer", "134.79.218.64:56789 UDP", 0, 0, 1)
initMksu("Mksu", "MksuServer")

#asynSetTraceIOMask("MksuServer",0,4)
#asynSetTraceMask("MksuServer",0,255)

dbLoadTemplate("mksu.substitutions")

iocInit()

