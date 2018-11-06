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
DEFINES		+= -arch x86_64

BUILD_LIBS	= -lboost_program_options

#
# File Extensions
#
SFILES		:= cc
DFILES		:= d
HFILES		:= hh
OFILES		:= o
GCHFILES	:= gch
AFILES		:= a
SOFILES		:= so
SYMFILES	:= dSYM

#
# Compiler Flags
#
CXX		:= g++
CXXFLAGS	:= -Wall -g -std=c++11
CXXFLAGS	+= -MMD -MP
CXXFLAGS	+= $(DEFINES)

#
# Linker Flags
#
LDFLAGS		:= -shared

#
# Archiver Flags
#
AR		:= ar
ARFLAGS		:= crs

SRCS = $(wildcard $(SRC)/**/*.$(SFILES))
DEPS = $(SRCS:%.$(SFILES)=%.$(DFILES))

SUBDIRS = $(CLASSES) $(CORE) $(DOC) $(EXTRAS) $(INC) $(SRC) $(TESTS)

DOXY		:= $(shell command -v doxygen 2> /dev/null)
DOXYTOUCH	:= $(DOC)/doxy

.PHONY: all
all: version engine core build main docs

.PHONY: engine
engine: librotorxor.$(SOFILES)

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
	@-rm -rf $(OBJ)/*.$(GCHFILES)

	@echo Cleaning library files...
	@-rm -rf $(LIB)/*.$(AFILES)
	@-rm -rf $(LIB)/*.$(SOFILES)

	@echo Cleaning $(TESTS)/
	@-rm -rf $(TESTS)/*.$(OFILES)

.PHONY: cleanbin
cleanbin:
	@echo Cleaning $(BUILD)/
	@-rm -rf $(BUILD)

.PHONY: cleandeps
cleandeps:
	@echo Cleaning dependencies...
	@-rm -rf $(CORE)/*.$(SYMFILES) $(CORE)/*.$(DFILES)
	@-rm -rf $(CLASSES)/*.$(SYMFILES) $(CLASSES)/*.$(DFILES)
	@-rm -rf $(EXTRAS)/*.$(SYMFILES) $(EXTRAS)/*.$(DFILES)
	@-rm -rf $(INC)/*.$(SYMFILES) $(INC)/*.$(DFILES)
	@-rm -rf $(SRC)/*.$(SYMFILES) $(SRC)/*.$(DFILES)
	@-rm -rf $(TESTS)/*.$(SYMFILES) $(TESTS)/*.$(DFILES)

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

-include $(DEPS)
include $(addsuffix /Makefile, $(SUBDIRS))
