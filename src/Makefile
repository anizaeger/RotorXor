# Main Executable

.PHONY: main.$(OFILES)
main.$(OFILES): $(OBJ)/main.$(OFILES)
$(OBJ)/main.$(OFILES): $(SRC)/main.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CLASSES)

$(BUILD)/$(PROGEXEC): $(OBJ)/basicSys.$(OFILES) \
	$(OBJ)/interface.$(OFILES) \
	$(LIB)/menu.$(AFILES) \
	$(OBJ)/interactive.$(OFILES) \
	$(LIB)/librotorxor.$(AFILES) \
	$(OBJ)/main.$(OFILES)
	@echo Linking main executable $@
	@$(CXX) $(CXXFLAGS) $(BUILD_LIBS) -o $(BUILD)/$(PROGEXEC) $^
	@rm -rf $(DOXYTOUCH)

.PHONY: main
main: $(BUILD)/$(PROGEXEC)
