INCL = master_hash.h ranson_check.h create_files.h filecheck.h
SRC = ransom_check.c master_hash.c master_check.c  create_files.c filecheck.c
OBJ = $(SRC:.c=.o)
LIBS =-lcrypto
EXE = ransom_check

# Compiler, Linker Defines
CC      = /usr/bin/gcc
CFLAGS  = 
LIBPATH = 
LDFLAGS = -o $(EXE) $(LIBPATH) $(LIBS)
CFDEBUG = -ansi -pedantic -Wall -g -DDEBUG $(LDFLAGS)
RM      = /bin/rm -f


# Compile and Assemble C Source Files into Object Files
%.o: %.c
	$(CC) -c $(CFLAGS) $*.c

# Link all Object Files with external Libraries into Binaries
$(EXE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS)

# Objects depend on these Libraries
$(OBJ): $(INCL)

# Create a gdb/dbx Capable Executable with DEBUG flags turned on
debug:
	$(CC) $(SRC)

# Clean Up Objects, Exectuables, Dumps out of source directory
clean:
	$(RM) $(OBJ)
