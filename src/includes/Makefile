#Includes

RX_LIB = $(OBJ)/base64.$(OFILES) $(OBJ)/basicSys.$(OFILES) $(OBJ)/fileio.$(OFILES) $(OBJ)/interface.$(OFILES) $(OBJ)/keyfile.$(OFILES) $(OBJ)/menu.$(OFILES) $(OBJ)/randgen.$(OFILES) $(OBJ)/tee.$(OFILES)

.PHONY: includes
includes: base64.$(OFILES) basicSys.$(OFILES) fileio.$(AFILES) interface.$(AFILES) keyfile.$(AFILES) menu.$(AFILES) randgen.$(AFILES) tee.$(OFILES)

#
# Base64 Translator
#
.PHONY: base64.$(OFILES)
base64.$(OFILES): $(OBJ)/base64.$(OFILES)
$(OBJ)/base64.$(OFILES): $(INC)/base64.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(INC)

#
# Basic Helpers
#
.PHONY: basicSys.$(OFILES)
basicSys.$(OFILES): $(OBJ)/basicSys.$(OFILES)
$(OBJ)/basicSys.$(OFILES): $(INC)/basicSys.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(INC)

#
# File I/O
#
.PHONY: fileio.$(AFILES)
fileio.$(AFILES): $(LIB)/fileio.$(AFILES)

$(LIB)/fileio.$(AFILES): $(OBJ)/fileio.$(OFILES) $(OBJ)/basicSys.$(OFILES) $(OBJ)/interface.$(OFILES)
	@echo Generating library $@
	@$(AR) $(ARFLAGS) $@ $^

$(OBJ)/fileio.$(OFILES): $(INC)/fileio.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(INC)

#
# User Interface Helpers
#

.PHONY: interface.$(AFILES)
interface.$(AFILES): $(LIB)/interface.$(AFILES)

$(LIB)/interface.$(AFILES): $(OBJ)/interface.$(OFILES) $(OBJ)/basicSys.$(OFILES)
	@echo Generating library $@
	@$(AR) $(ARFLAGS) $@ $^

$(OBJ)/interface.$(OFILES): $(INC)/interface.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(INC)

#
# CSPRNG Keyfile
#
.PHONY: keyfile.$(AFILES)
keyfile.$(AFILES): $(LIB)/keyfile.$(AFILES)

$(LIB)/keyfile.$(AFILES): $(OBJ)/keyfile.$(OFILES) $(OBJ)/base64.$(OFILES)
	@echo Generating library $@
	@$(AR) $(ARFLAGS) $@ $^

$(OBJ)/keyfile.$(OFILES): $(INC)/keyfile.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(INC)

#
# Menu Interface
#
.PHONY: menu.$(AFILES)
menu.$(AFILES): $(LIB)/menu.$(AFILES)

$(LIB)/menu.$(AFILES): $(OBJ)/menu.$(OFILES) $(OBJ)/basicSys.$(OFILES)
	@echo Generating library $@
	@$(AR) $(ARFLAGS) $@ $^

$(OBJ)/menu.$(OFILES): $(INC)/menu.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(INC)

#
# Blum Blum Shub CSPRNG
#
.PHONY: randgen.$(AFILES)
randgen.$(AFILES): $(LIB)/randgen.$(AFILES)

$(LIB)/randgen.$(AFILES): $(OBJ)/randgen.$(OFILES) $(OBJ)/keyfile.$(OFILES) $(OBJ)/base64.$(OFILES)
	@echo Generating library $@
	@$(AR) $(ARFLAGS) $@ $^

$(OBJ)/randgen.$(OFILES): $(INC)/randgen.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(INC)

#
# Tee Outout
#
.PHONY: tee.$(OFILES)
tee.$(OFILES): $(OBJ)/tee.$(OFILES)
$(OBJ)/tee.$(OFILES): $(INC)/tee.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(INC)
