# Main Executable

.PHONY: main.$(OFILES)
main.$(OFILES): $(OBJ)/main.$(OFILES)
$(OBJ)/main.$(OFILES): $(SRC)/main.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD)/$(PROGEXEC): $(OBJ)/basicSys.$(OFILES) \
	$(OBJ)/interactive.$(OFILES) \
	$(OBJ)/menu.$(OFILES) \
	$(OBJ)/main.$(OFILES)
	@echo Linking main executable $@
	@$(CXX) $(CXXFLAGS) -lboost_program_options -o $(BUILD)/$(PROGEXEC) $^
	@rm -rf $(DOXYTOUCH)

.PHONY: main
main: $(BUILD)/$(PROGEXEC)
