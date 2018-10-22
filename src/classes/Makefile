# Classes

classes: charGen.$(OFILES) charSet.$(OFILES) drum.$(OFILES) pulser.$(OFILES) rotor.$(OFILES) rotorBank.$(OFILES) scrambler.$(OFILES) xorer.$(OFILES) handler.$(OFILES)
.PHONY: classes

.PHONY: charGen.$(OFILES)
charGen.$(OFILES): $(OBJ)/charGen.$(OFILES)
$(OBJ)/charGen.$(OFILES): $(CLASSES)/charGen.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CLASSES)

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

.PHONY: rotorXor.$(OFILES)
rotorXor.$(OFILES): $(OBJ)/rotorXor.$(OFILES)
$(OBJ)/rotorXor.$(OFILES): $(CLASSES)/rotorXor.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CLASSES)
