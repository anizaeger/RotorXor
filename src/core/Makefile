# Core

core: interactive.$(OFILES) keyMngr.$(OFILES)

.PHONY: interactive.$(OFILES)
interactive.$(OFILES): $(OBJ)/interactive.$(OFILES)
$(OBJ)/interactive.$(OFILES): $(CORE)/interactive.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CORE)

.PHONY: keyMngr.$(OFILES)
keyMngr.$(OFILES): $(OBJ)/keyMngr.$(OFILES)
$(OBJ)/keyMngr.$(OFILES): $(CORE)/keyMngr.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CORE)
