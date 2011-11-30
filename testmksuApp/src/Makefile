# Makefile
TOP = ../..
ifdef EPICS_HOST_ARCH

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

# <name>.dbd will be created from <name>Include.dbd
DBD += example.dbd
example_DBD += base.dbd
example_DBD += asyn.dbd
example_DBD += drvAsynIPPort.dbd
example_DBD += mksu.dbd

#=============================

PROD_IOC = example

# <name>_registerRecordDeviceDriver.cpp will be created from <name>.dbd
example_SRCS += example_registerRecordDeviceDriver.cpp
example_SRCS_DEFAULT += exampleMain.cc
example_SRCS_vxWorks += -nil-

#The following adds support from base/src/vxWorks
example_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

#example_LIBS_DEFAULT += recIoc
#example_LIBS_DEFAULT += softDevIoc
#example_LIBS_DEFAULT += testDevIoc

example_LIBS += mksu
mksu_DIR = $(INSTALL_LIB)

example_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

else

include $(TOP)/config/CONFIG_APP
include $(TOP)/config/RULES_ARCHS

endif
