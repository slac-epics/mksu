# Makefile
TOP = ../..
ifdef EPICS_HOST_ARCH

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

# No optimization, we want debugging info:
HOST_OPT=NO

USR_CPPFLAGS += -DDEBUG_PRINT

DBD = mksu.dbd

LIBRARY_IOC = mksu

# create munch file for dynamic loading will install in <bin>
PROD_IOC_vxWorks += mksuLib

LIB_LIBS += asyn
LIB_LIBS += $(EPICS_BASE_IOC_LIBS) 

mksu_SRCS += Log.cc
mksu_SRCS += MksuDriver.cc
mksu_SRCS += MksuComm.cc
mksu_SRCS += Commands.cc

# The PROD_IOC_vxWorks is built from the same srcs and must include
# the registry routines.
mksuLib_SRCS+=$(mksu_SRCS)
mksuLib_SRCS+=mksu_registerRecordDeviceDriver.cpp

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

else

include $(TOP)/config/CONFIG_APP
include $(TOP)/config/RULES_ARCHS

endif
