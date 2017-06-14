CPPFLAGS += -O2  -s  -Wall
CPP       =  g++


# list of tests for build
TESTS  = linux_spi_test




.PHONY: all
all: clean  $(TESTS)



.PHONY: clean
clean:
	-@rm -f *.o
	-@rm -f *.*~
	-@rm -f $(TESTS)



.PHONY: $(TESTS)
$(TESTS):
	$(CPP)  $@.cpp linux_spi.cpp -o $@  -DTEST_NAME='"$@"'  $(CPPFLAGS)
	@echo "  ---- Compiled $@ ----"
	@echo ""



.PHONY: help
help:
	@echo "make [command]"
	@echo "command is:"
	@echo "   clean   -  remove all binary files"
	@echo "   all     -  clean and build all tests"
	@echo "   help    -  This help"

