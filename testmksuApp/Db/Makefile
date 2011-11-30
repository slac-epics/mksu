# Makefile.Host
TOP = ../..
ifdef EPICS_HOST_ARCH

include $(TOP)/configure/CONFIG

#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#----------------------------------------------------
#  Optimization of DB files using dbst (DEFAULT: NO)
#DB_OPT = YES

#----------------------------------------------------
# Add databases, templates, substitutions like this

DB += mksu.template


include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

else

include $(TOP)/config/CONFIG_APP
include $(TOP)/config/RULES_ARCHS

endif
