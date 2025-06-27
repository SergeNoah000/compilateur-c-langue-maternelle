# List of C source files
SOURCES := $(wildcard *.c)
# List of executables to be generated
EXECUTABLES := $(SOURCES:.c=)

# Default target, builds all executables
all: $(EXECUTABLES)

# Pattern rule to build an executable from a C source file
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean target to remove all executables
clean:
	rm -f $(EXECUTABLES)

# Pattern rule to clean a specific executable
clean-%:
	rm -f $*

# Convenience target to compile all .c files
compile-all: all

# Convenience target to clean all .c files
clear-all: clean

.PHONY: all clean compile-all clear-all
