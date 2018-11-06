# Core

core: interactive.$(OFILES) keyDB.$(OFILES)

.PHONY: interactive.$(OFILES)
interactive.$(OFILES): $(OBJ)/interactive.$(OFILES)
$(OBJ)/interactive.$(OFILES): $(CORE)/interactive.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CORE)

.PHONY: keyDB.$(OFILES)
keyDB.$(OFILES): $(OBJ)/keyDB.$(OFILES)
$(OBJ)/keyDB.$(OFILES): $(CORE)/keyDB.$(SFILES)
	@echo Compiling $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	@mv $(patsubst %.o, %.d, $@) $(CORE)
