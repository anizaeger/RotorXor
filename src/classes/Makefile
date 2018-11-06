# Classes

RX_OBJ		= $(OBJ)/base64.$(OFILES) $(OBJ)/keyfile.$(OFILES) $(OBJ)/randgen.$(OFILES) $(OBJ)/charGen.$(GCHFILES) $(OBJ)/charSet.$(OFILES) $(OBJ)/drum.$(OFILES) $(OBJ)/pulser.$(OFILES) $(OBJ)/rotor.$(OFILES) $(OBJ)/rotorBank.$(OFILES) $(OBJ)/rxMngr.$(OFILES) $(OBJ)/scrambler.$(OFILES) $(OBJ)/xorer.$(OFILES) $(OBJ)/handler.$(OFILES)

classes: charGen.$(GCHFILES) charSet.$(OFILES) drum.$(OFILES) pulser.$(OFILES) rotor.$(OFILES) rotorBank.$(OFILES) rxMngr.$(OFILES) scrambler.$(OFILES) xorer.$(OFILES) handler.$(OFILES)
.PHONY: classes

.PHONY: charGen.$(GCHFILES)
charGen.$(GCHFILES): $(OBJ)/charGen.$(GCHFILES)
$(OBJ)/charGen.$(GCHFILES): $(CLASSES)/charGen.$(HFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.gch, %.d, $@) $(CLASSES)

.PHONY: charSet.$(OFILES)
charSet.$(OFILES): $(OBJ)/charSet.$(OFILES)
$(OBJ)/charSet.$(OFILES): $(CLASSES)/charSet.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CLASSES)

.PHONY: drum.$(OFILES)
drum.$(OFILES): $(OBJ)/drum.$(OFILES)
$(OBJ)/drum.$(OFILES): $(CLASSES)/drum.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CLASSES)

.PHONY: pulser.$(OFILES)
pulser.$(OFILES): $(OBJ)/pulser.$(OFILES)
$(OBJ)/pulser.$(OFILES): $(CLASSES)/pulser.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CLASSES)

.PHONY: rotor.$(OFILES)
rotor.$(OFILES): $(OBJ)/rotor.$(OFILES)
$(OBJ)/rotor.$(OFILES): $(CLASSES)/rotor.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CLASSES)

.PHONY: rotorBank.$(OFILES)
rotorBank.$(OFILES): $(OBJ)/rotorBank.$(OFILES)
$(OBJ)/rotorBank.$(OFILES): $(CLASSES)/rotorBank.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CLASSES)

.PHONY: scrambler.$(OFILES)
scrambler.$(OFILES): $(OBJ)/scrambler.$(OFILES)
$(OBJ)/scrambler.$(OFILES): $(CLASSES)/scrambler.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CLASSES)

.PHONY: xorer.$(OFILES)
xorer.$(OFILES): $(OBJ)/xorer.$(OFILES)
$(OBJ)/xorer.$(OFILES): $(CLASSES)/xorer.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CLASSES)

.PHONY: handler.$(OFILES)
handler.$(OFILES): $(OBJ)/handler.$(OFILES)
$(OBJ)/handler.$(OFILES): $(CLASSES)/handler.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CLASSES)

.PHONY: rxMngr.$(OFILES)
rxMngr.$(OFILES): $(OBJ)/rxMngr.$(OFILES)
$(OBJ)/rxMngr.$(OFILES): $(CLASSES)/rxMngr.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CLASSES)

.PHONY: librotorxor.$(SOFILES)
librotorxor.$(SOFILES): $(LIB)/librotorxor.$(SOFILES)
$(LIB)/librotorxor.$(SOFILES): $(LIB)/librotorxor.$(AFILES)
	@echo Generating shared library $@
	@$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

.PHONY: librotorxor.$(AFILES)
librotorxor.$(AFILES): $(LIB)/librotorxor.$(AFILES)
$(LIB)/librotorxor.$(AFILES): $(RX_OBJ) \
	$(OBJ)/base64.$(OFILES) \
	$(OBJ)/keyfile.$(OFILES) \
	$(OBJ)/randgen.$(OFILES)
	@echo Generating library $@
	@$(AR) $(ARFLAGS) $@ $^