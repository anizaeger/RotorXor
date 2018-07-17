#
# Documentation Generation and Management
#

.PHONY: docs
docs: $(DOXYTOUCH)

$(DOXYTOUCH): Doxyfile
ifndef DOXY
	@echo Doxygen not installed, unable to generate documentation.
else
	@echo Generating documentation for $(PROGVER)
	@( cat Doxyfile ; echo "PROJECT_NUMBER=v$(VERSION)" ) | doxygen -
	@echo "Documentation generated: `date +%Y-%m-%dT%H:%M:%S%z`" >  $(DOC)/doxy
endif

.PHONY: pdf
pdf: $(DOC)/latex/Makefile
	@cd $(DOC)/latex && $(MAKE)
