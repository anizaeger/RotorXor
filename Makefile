#
# Directory definitions
#
TOP		:= $(shell pwd)
BUILD		:= $(TOP)/build
DEP		:= $(TOP)/.deps
DOC		:= $(TOP)/doc
LIB		:= $(TOP)/lib
OBJ		:= $(TOP)/obj
SRC		:= $(TOP)/src
CORE		:= $(SRC)/core
CLASSES		:= $(SRC)/classes
EXTRAS		:= $(SRC)/extras
INC		:= $(SRC)/includes
TESTS		:= $(SRC)/tests
BINDIR		:= $(HOME)/bin

#
# Project and executable name
#
PROGNAME	 = RotorXor
PROGEXEC	 = rotorxor

DEFINES		:= -DP_NAME=$(PROGNAME)
DEFINES		+= -DP_EXEC=$(PROGEXEC)

#
# Program Version Number
#
CONST		:= $(SRC)/constants.hh
GET_V		 = $(shell sed -n 's/.*$1 \([0-9*]\)/\1/p' $(CONST))
MAJOR		:= $(call GET_V,MAJOR)
MINOR		:= $(call GET_V,MINOR)
REVISION	:= 1
VERSION		:= $(MAJOR).$(MINOR).$(REVISION)
PROGVER		:= $(PROGNAME) v$(VERSION)

DEFINES		+= -DV_REVISION=$(REVISION)

#
# Program Directories
#
KEYDIR		:= $(HOME)/.rotorXor/keys

DEFINES		+= -DU_HOMEDIR=$(HOME)
DEFINES		+= -DU_KEYDIR=$(KEYDIR)

#
# File Extensions
#
SFILES		:= cc
DFILES		:= d
OFILES		:= o
AFILES		:= a
SYMFILES	:= dSYM

#
# Compiler Flags
#
CXX		:= g++
CXXFLAGS	:= -Wall -g -std=c++11
CXXFLAGS	+= -MMD -MP
CXXFLAGS	+= $(DEFINES)

SRCS = $(wildcard $(SRC)/**/*.$(SFILES))

SUBDIRS = $(CLASSES) $(CORE) $(DOC) $(EXTRAS) $(INC) $(SRC) $(TESTS)

DOXY		:= $(shell command -v doxygen 2> /dev/null)
DOXYTOUCH	:= $(DOC)/doxy

.PHONY: all
all: version build includes classes core main docs

.PHONY: version
version:
	@echo Making $(PROGVER)

build:
	@mkdir $@

.PHONY: cleanall
cleanall: clean cleandocs cleanbin

.PHONY: clean
clean: cleandeps

	@echo Cleaning $(SRC)/
	@-rm -rf $(SRC)/*.$(SRC)

	@echo Cleaning $(CORE)/
	@-rm -rf $(CORE)/*.$(OFILES)

	@echo Cleaning $(CLASSES)/
	@-rm -rf $(CLASSES)/*.$(OFILES)

	@echo Cleaning $(EXTRAS)/
	@-rm -rf $(EXTRAS)/*.$(OFILES)

	@echo Cleaning $(INC)/
	@-rm -rf $(INC)/*.$(OFILES)

	@echo Cleaning object files...
	@-rm -rf $(OBJ)/*.$(OFILES)

	@echo Cleaning library files...
	@-rm -rf $(LIB)/*.$(AFILES)

	@echo Cleaning $(TESTS)/
	@-rm -rf $(TESTS)/*.$(OFILES)

.PHONY: cleanbin
cleanbin:
	@echo Cleaning $(BUILD)/
	@-rm -rf $(BUILD)

.PHONY: cleandeps
cleandeps:
	@echo Cleaning dependencies...
	@-rm -rf $(CORE)/*.$(DFILES) $(CORE)/*.$(SYMFILES)
	@-rm -rf $(CLASSES)/*.$(DFILES) $(CLASSES)/*.$(SYMFILES)
	@-rm -rf $(EXTRAS)/*.$(DFILES) $(EXTRAS)/*.$(SYMFILES)
	@-rm -rf $(INC)/*.$(DFILES) $(INC)/*.$(SYMFILES)
	@-rm -rf $(SRC)/*.$(DFILES) $(SRC)/*.$(SYMFILES)
	@-rm -rf $(TESTS)/*.$(DFILES) $(TESTS)/*.$(SYMFILES)

.PHONY: cleandocs
cleandocs:
	@echo Cleaning $(DOC)/
	@-rm -rf $(DOC)/html
	@-rm -rf $(DOC)/latex
	@-rm -rf $(DOXYTOUCH)

.PHONY: install
install: all
	@echo Installing RotorXor...
	@mv $(BUILD)/$(PROGEXEC) $(HOME)/bin
	@mkdir -p $(KEYDIR)

-include $(SRCS:%.$(SFILES)=%.$(DFILES))
include $(addsuffix /Makefile, $(SUBDIRS))
