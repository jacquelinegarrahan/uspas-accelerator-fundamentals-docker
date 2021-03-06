#              $Id: GNUmakefile.in,v 1.40 2010/07/30 03:18:25 abh Exp $

#------------------------------------------------------------------------------#
#                             C o m p o n e n t s                              #
#------------------------------------------------------------------------------#

# Tell GNU make >=3.79 not to run the top level in parallel since
# inter sub-makefile dependencies are not correct. Should use flat Makefile.
# (F. Rademakers, 31 Oct 2005)
.NOTPARALLEL:

# Order in which components must be made
#
XRDCOMMON  = XrdSys XrdOuc XrdNet XrdSec

XRDSEC  = XrdSut XrdCrypto   XrdSecpwd XrdSecsss   XrdSecunix

SERVER  = XrdSfs XrdAcc Xrd \
          XrdOss XrdBwm XrdFrm XrdCms XrdOfs XrdRootd XrdXrootd

XRDCLIENT = XrdClient

XRDMON    = XrdMon

XRDPOSIX  = XrdPosix XrdPss XrdCns XrdApps

TARGETS = $(XRDCOMMON) $(XRDSEC) $(SERVER) $(XRDCLIENT)  $(XRDPOSIX)

ARCH    = x86_64_linux
ARCHDIR = 

ECHO    = 

TYPE    = Linux

RM      = /bin/rm
LN      = /bin/ln

#
# Envvars influencing what 'make install' does
export INSTPFX = /opt/xrootd
export LIBPATH = 
export ETCPATH = 
export BINPATH = 
export UTILSPATH = 
export INCPATH = 

#------------------------------------------------------------------------------#
#                                  R u l e s                                   #
#------------------------------------------------------------------------------#

all:
	@$(MAKE) $(TARGETS) MAKEXEQ=all XMSG=Making XDBG= --no-print-directory
	@if [ "x$(ARCHDIR)" != "x" ]; then \
	    $(RM) -fr bin/arch lib/arch obj/arch;\
	    $(LN) -s ./$(ARCH)  bin/arch;\
	    $(LN) -s ./$(ARCH)  lib/arch;\
	    $(LN) -s ./$(ARCH)  obj/arch;\
	fi
	@echo Make all done

perlmodule:
	@$(MAKE) $(XRDCLIENT) XrdClientPerl MAKEXEQ=perlmodule XMSG=Making XDBG=debug --no-print-directory
	@if [ "x$(ARCHDIR)" != "x" ]; then \
	    $(RM) -fr bin/arch_dbg lib/arch_dbg;\
	    $(LN) -s ./$(ARCH)_dbg  bin/arch_dbg;\
	    $(LN) -s ./$(ARCH)_dbg  lib/arch_dbg;\
	fi
	@echo Make perlmodule done

clean: FORCE
	@$(MAKE) $(TARGETS) MAKEXEQ=clean XMSG=Cleaning --no-print-directory
	@if [ "x$(ARCHDIR)" != "x" ]; then \
	   $(RM) -fr bin/arch lib/arch;\
	   $(RM) -fr bin/$(ARCHDIR) lib/$(ARCHDIR) obj/$(ARCHDIR);\
	   if [ "$(TYPE)" = "sunos" ]; then \
	      $(RM) -fr obj/$(ARCH)$(SUNCACHE);\
	      $(RM) -fr obj/$(ARCH)/dbg$(SUNCACHE);\
	   fi;\
	else \
	   $(RM) -fr bin lib obj;\
	   if [ "$(TYPE)" = "sunos" ]; then \
	      $(RM) -fr obj$(SUNCACHE);\
	   fi;\
	fi
	$(ECHO)$(RM) -f src/XrdOuc/XrdOucFactoryBonjour.*
	$(ECHO)$(RM) -f test-comp.*

distclean: FORCE
	@$(MAKE) $(TARGETS) MAKEXEQ=clean XMSG=Cleaning --no-print-directory
	$(ECHO)$(RM) -fr bin lib obj
	$(ECHO)$(RM) -f GNUmakefile
	$(ECHO)$(RM) -f src/GNUmake.env
	$(ECHO)$(RM) -f src/GNUmake.options
	$(ECHO)$(RM) -f config.log
	$(ECHO)$(RM) -f test-comp.*
	$(ECHO)$(RM) -f src/XrdOuc/XrdOucFactoryBonjour.*

install: FORCE
	@echo Installing...
	$(ECHO) ./makeinstall.sh ./ /opt/xrootd

XrdAcc: FORCE
	@echo $(XMSG) acc $(XDBG) component...
	$(ECHO)cd src/XrdAcc;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdApps: FORCE
	@echo $(XMSG) apps $(XDBG) component...
	$(ECHO)cd src/XrdApps;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdBwm: FORCE
	@echo $(XMSG) bwm $(XDBG) component...
	$(ECHO)cd src/XrdBwm;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdClient: FORCE
	@echo $(XMSG) client $(XDBG) component...
	@cd src/XrdClient;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdClientPerl: FORCE
	@echo $(XMSG) admin client perl wrapper $(XDBG) component...
	@cd src/XrdClient;\
	$(MAKE) perlmod ARCH=$(ARCH) --no-print-directory

XrdCms: FORCE
	@echo $(XMSG) cms $(XDBG) component...
	$(ECHO)cd src/XrdCms;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdCns: FORCE
	@echo $(XMSG) cns $(XDBG) component...
	$(ECHO)cd src/XrdCns;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdCrypto: FORCE
	@echo $(XMSG) crypto $(XDBG) component...
	$(ECHO)cd src/XrdCrypto;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdNet: FORCE
	@echo $(XMSG) net $(XDBG) component...
	@cd src/XrdNet;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdFrm: FORCE
	@echo $(XMSG) frm $(XDBG) component...
	@cd src/XrdFrm;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdOfs: FORCE
	@echo $(XMSG) ofs $(XDBG) component...
	$(ECHO)cd src/XrdOfs;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdOss: FORCE
	@echo $(XMSG) oss $(XDBG) component...
	$(ECHO)cd src/XrdOss;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdOuc: FORCE
	@echo $(XMSG) ouc $(XDBG) component...
	$(ECHO)cd src/XrdOuc;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdMon:	FORCE
	@echo $(XMSG) mon $(XDBG) component...
	$(ECHO)cd src/XrdMon;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdPosix: FORCE
	@echo $(XMSG) posix $(XDBG) component...
	$(ECHO)cd src/XrdPosix;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdPss: FORCE
	@echo $(XMSG) pss $(XDBG) component...
	$(ECHO)cd src/XrdPss;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdSfs: FORCE
	@echo $(XMSG) sfs $(XDBG) component...
	$(ECHO)cd src/XrdSfs;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdSys: FORCE
	@echo $(XMSG) sys $(XDBG) component...
	$(ECHO)cd src/XrdSys;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdRootd: FORCE
	@echo $(XMSG) rootd $(XDBG) component...
	$(ECHO)cd src/XrdRootd;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdSec: FORCE
	@echo $(XMSG) sec $(XDBG) component...
	$(ECHO)cd src/XrdSec;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdSecgsi: FORCE
	@echo $(XMSG) secgsi $(XDBG) component...
	$(ECHO)cd src/XrdSecgsi;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdSeckrb4: FORCE
	@echo $(XMSG) seckrb4 $(XDBG) component...
	$(ECHO)cd src/XrdSeckrb4;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdSeckrb5: FORCE
	@echo $(XMSG) seckrb5 $(XDBG) component...
	$(ECHO)cd src/XrdSeckrb5;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdSecpwd: FORCE
	@echo $(XMSG) secpwd $(XDBG) component...
	$(ECHO)cd src/XrdSecpwd;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdSecssl: FORCE
	@echo $(XMSG) secssl $(XDBG) component...
	$(ECHO)cd src/XrdSecssl;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdSecsss: FORCE
	@echo $(XMSG) secsss $(XDBG) component...
	$(ECHO)cd src/XrdSecsss;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdSecunix: FORCE
	@echo $(XMSG) secunix $(XDBG) component...
	$(ECHO)cd src/XrdSecunix;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdSut: FORCE
	@echo $(XMSG) sut "(sec utils)" $(XDBG) component...
	$(ECHO)cd src/XrdSut;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

Xrd: FORCE
	@echo $(XMSG) xrd $(XDBG) component...
	$(ECHO)cd src/Xrd;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

XrdXrootd: FORCE
	@echo $(XMSG) xrootd $(XDBG) component...
	$(ECHO)cd src/XrdXrootd;\
	$(MAKE) $(MAKEXEQ) ARCH=$(ARCH) --no-print-directory

FORCE: ;
