#
# Simple Makefile for my C Processor as command processor..
#

all: pre-build main-build

pre-build: 
	@echo ">>> PRE BUILD <<<"

	@if [ -e ./cicanura ]; \
	then \
		(cd cicanura && git pull); \
	else \
		git clone https://github.com/rludva/cicanura.git; \
	fi;

	(cd cicanura && make target);

post-build:
	@echo ">>> POST BUILD <<<"
	@$(MAKE) --no-print-directory tests

main-build: target 
	@$(MAKE) --no-print-directory post-build

# Run the tests..
tests:
	@if [ ! -e ./test_runner/test_runner ]; \
	then \
		echo "Error: ./test_runner/test_runner is not exist!"; \
		echo ""; \
	fi

	@./cicanura/test_runner/test_runner
	@./test_runner/test_runner

# Target for test_runner..
target: \
	./application/interface.o \
	./core/test/test_cprocessor.o \
	./core/source/cprocessor.o \
	./test_runner/test_runner.o


	cc -o ./application/interface \
		./application/interface.o \
		./cicanura/core/source/strings.o \
		./cicanura/core/source/collection.o \
		./core/source/cprocessor.o 

	# Build test_runner..
	cc -o ./test_runner/test_runner \
		./test_runner/test_runner.o \
		./core/test/test_cprocessor.o \
		./core/source/cprocessor.o \
		./cicanura/core/source/strings.o \
		./cicanura/core/source/collection.o \
		./cicanura/core/source/ctest.o


# C Processor
./core/source/cprocessor.o: \
	./core/source/cprocessor.c \
	./core/include/cprocessor.h

# Test for C Processor
./core/test/test_cprocessor.o: \
	./core/test/test_cprocessor.c \
	./core/source/cprocessor.o

# Test runner
./test_runner/test_runner.o: \
	./test_runner/test_runner.c \
	./core/test/test_cprocessor.o \
	./core/source/cprocessor.o \
	./cicanura/core/source/ctest.o

#
./application/interface.o: \
	./application/interface.c \
	./core/include/cprocessor.h 

# Clean the outputs..
clean:
	@(cd cicanura && make clean);

	@for soubor in \
		./application/interface \
		./application/interface.o \
		./core/test/test_cprocessor.o \
		./core/source/cprocessor.o \
		./test_runner/test_runner.o \
		./test_runner/test_runner; \
	do \
		if [ -e $$soubor ]; \
		then \
			echo "Removing: $$soubor"; \
			rm $$soubor; \
		fi; \
	done
	
