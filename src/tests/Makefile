# Tests

BINFILES 	= charGenTest rotorTest bankTest scramblerTest pulseTest xorTest cipherTest

.PHONY: tests
tests: build $(BINFILES) docs

# Character Generator Test

.PHONY: charGenTest.$(OFILES)
charGenTest.$(OFILES): $(OBJ)/charGenTest.$(OFILES)
$(OBJ)/charGenTest.$(OFILES): $(TESTS)/charGenTest.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(TESTS)

.PHONY: charGenTest
charGenTest: build $(BUILD)/charGenTest
$(BUILD)/charGenTest: $(LIB)/interface.$(AFILES) $(LIB)/randgen.$(AFILES) \
	$(OBJ)/charSet.$(OFILES) $(OBJ)/charGen.$(OFILES) \
	$(OBJ)/charGenTest.$(OFILES)
	@echo Linking $@
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@rm -rf $(DOXYTOUCH)

# Rotor Test

.PHONY: rotorTest.$(OFILES)
rotorTest.$(OFILES): $(OBJ)/rotorTest.$(OFILES)
$(OBJ)/rotorTest.$(OFILES): $(TESTS)/rotorTest.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(TESTS)

.PHONY: rotorTest
rotorTest: build $(BUILD)/rotorTest
$(BUILD)/rotorTest: $(LIB)/interface.$(AFILES) $(LIB)/randgen.$(AFILES) \
	$(OBJ)/charSet.$(OFILES) $(OBJ)/drum.$(OFILES) $(OBJ)/rotor.$(OFILES) \
	$(OBJ)/rotorTest.$(OFILES)
	@echo Linking $@
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@rm -rf $(DOXYTOUCH)

# Rotor Bank Test

.PHONY: bankTest.$(OFILES)
bankTest.$(OFILES): $(OBJ)/bankTest.$(OFILES)
$(OBJ)/bankTest.$(OFILES): $(TESTS)/bankTest.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(TESTS)

.PHONY: bankTest
bankTest: build $(BUILD)/bankTest
$(BUILD)/bankTest: $(LIB)/interface.$(AFILES) $(LIB)/randgen.$(AFILES) \
	$(OBJ)/charSet.$(OFILES) $(OBJ)/drum.$(OFILES) $(OBJ)/rotor.$(OFILES) \
	$(OBJ)/rotorBank.$(OFILES) \
	$(OBJ)/bankTest.$(OFILES)
	@echo Linking $@
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@rm -rf $(DOXYTOUCH)

# Scrambler Test

.PHONY: scramblerTest.$(OFILES)
scramblerTest.$(OFILES): $(OBJ)/scramblerTest.$(OFILES)
$(OBJ)/scramblerTest.$(OFILES): $(TESTS)/scramblerTest.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(TESTS)

.PHONY: scramblerTest
scramblerTest: build $(BUILD)/scramblerTest
$(BUILD)/scramblerTest: $(LIB)/interface.$(AFILES) $(LIB)/randgen.$(AFILES) \
	$(OBJ)/charSet.$(OFILES) $(OBJ)/drum.$(OFILES) $(OBJ)/rotor.$(OFILES) \
	$(OBJ)/rotorBank.$(OFILES) $(OBJ)/scrambler.$(OFILES) \
	$(OBJ)/scramblerTest.$(OFILES)
	@echo Linking $@
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@rm -rf $(DOXYTOUCH)

# Pulser Test

.PHONY: pulseTest.$(OFILES)
pulseTest.$(OFILES): $(OBJ)/pulseTest.$(OFILES)
$(OBJ)/pulseTest.$(OFILES): $(TESTS)/pulseTest.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(TESTS)

.PHONY: pulseTest
pulseTest: build $(BUILD)/pulseTest
$(BUILD)/pulseTest: $(LIB)/interface.$(AFILES) $(LIB)/randgen.$(AFILES) \
	$(OBJ)/charSet.$(OFILES) $(OBJ)/drum.$(OFILES) $(OBJ)/rotor.$(OFILES) \
	$(OBJ)/rotorBank.$(OFILES) $(OBJ)/scrambler.$(OFILES) $(OBJ)/pulser.$(OFILES)\
	$(OBJ)/pulseTest.$(OFILES)
	@echo Linking $@
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@rm -rf $(DOXYTOUCH)

# Xor Test

.PHONY: xorTest.$(OFILES)
xorTest.$(OFILES): $(OBJ)/xorTest.$(OFILES)
$(OBJ)/xorTest.$(OFILES): $(TESTS)/xorTest.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(TESTS)

.PHONY: xorTest
xorTest: build $(BUILD)/xorTest
$(BUILD)/xorTest: $(LIB)/interface.$(AFILES) $(LIB)/randgen.$(AFILES) \
	$(OBJ)/charSet.$(OFILES) $(OBJ)/drum.$(OFILES) $(OBJ)/rotor.$(OFILES) \
	$(OBJ)/rotorBank.$(OFILES) $(OBJ)/scrambler.$(OFILES) $(OBJ)/pulser.$(OFILES) $(OBJ)/xorer.$(OFILES) \
	$(OBJ)/xorTest.$(OFILES)
	@echo Linking $@
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@rm -rf $(DOXYTOUCH)

# Cipher Test

.PHONY: cipherTest.$(OFILES)
cipherTest.$(OFILES): $(OBJ)/cipherTest.$(OFILES)
$(OBJ)/cipherTest.$(OFILES): $(TESTS)/cipherTest.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(TESTS)

.PHONY: cipherTest
cipherTest: build $(BUILD)/cipherTest
$(BUILD)/cipherTest: $(LIB)/interface.$(AFILES) $(LIB)/randgen.$(AFILES) \
	$(OBJ)/charSet.$(OFILES) $(OBJ)/drum.$(OFILES) $(OBJ)/rotor.$(OFILES) \
	$(OBJ)/rotorBank.$(OFILES) $(OBJ)/scrambler.$(OFILES) $(OBJ)/pulser.$(OFILES) $(OBJ)/xorer.$(OFILES) $(OBJ)/handler.$(OFILES) \
	$(OBJ)/cipherTest.$(OFILES)
	@echo Linking $@
	@$(CXX) $(CXXFLAGS) -o $@ $^
	@rm -rf $(DOXYTOUCH)
