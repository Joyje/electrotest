#Compilator to use
CC=gcc

#FLags:
#-fPIC: Position Independent Code. The generated machine code is not dependent
#on being located on a specific address. This is used for shared libraries that
#be moved to another address in memory.
#-Werror: Makes all warnings to errors.
#-Wextra: Enalbkes some extra warnings that are not included in "-Werror".
#-O2: Optimize the performance of the generated code (but increases compilation
#time and memory usage.
CFLAGS = -fPIC -Werror -Wextra -O2

#Linking flags
#Produces a shared object. You need also to use "-fPIC" flag during compilaton
#when this flag is used.
LDFLAGS = -shared

#Sources
SOURCES = libcomponent.c

#Object file to generate
OBJ = libcomponent.o

#Lib target name
TARGET = libcomponent.so

#Installation directory for library
LIBDIR = /usr/local/lib/

#Test
#Show all warnings
TESTFLAGS = -Wall
#Dir where the tests are executed
TESTDIR = $(CURPATH)
TESTSOURCES = componentTest.c
TESTOBJ = componentTest.o
#Executable file to run
TESTTARGET = componentTest
#Directory where the lib to include is located
LIB_DIR = $(CURPATH)
#Linking for componentTest application
#-L: Looks in a directory for library files
#-l: search for library component when linking
#-W1, -rpath=$(CURDIR): -W1 states that an at least one option
#should be passed to the linker and then the options are set
#by comma separated string. "-rpath" Adds a directory to the run-time
#library search path. In this time the directory where you compile
#-lm: -l as link and m for linking math library which is used
LD = -L$(CURDIR) -lcomponent -Wl,-rpath=$(CURDIR) -lm

#Make all will build the libcomponent.so file
all: $(TARGET)

#Object file depends on c files which depends on h-files
libcomonent.o: libcomponent.c libcomponent.h

#To generate the o-file make needs to compile the c-files using
#compiler stated in CC makro. $@ says that the compilation output
#should be put in filename stated on the left hand of the ":" on
#row above. The $< is the source file
#-c: Compiles source file without linking
#-o: The build output (in this case the libcomponent.so)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(CFLAGS)

#Installation of library
install:
	cp $(TARGET) $(LIBDIR).

#Removes installed files
uninstall:
	rm -f $(LIBDIR)$(TARGET)

#Removes compiled files and temprary files
clean:
	$(RM) $(TARGET) *.o *~
	$(RM) $(TESTDIR)$(TESTTARGET) $(TESTDIR)*.o $(TESTDIR)*~

#####The rest of this file are specific for the unit tests
#make test makes the test executable
test: $(TESTDIR)$(TESTTARGET)

#Use testflags to compile the tests
$(TESTDIR)$(TESTOBJ): $(TESTDIR)$(TESTSOURCES)
	$(CC) -c -o $@ $< $(TESTFLAGS) $(LD)

$(TESTDIR)$(TESTTARGET): $(TESTDIR)$(TESTOBJ)
	$(CC) -o $@ $^ $(TESTFLAGS) $(LD)

#make check runs the test application componentTest
check:
	./$(TESTTARGET)
