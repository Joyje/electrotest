#Compilator to use
CC=gcc
#FLags to show all warnings
CFLAGS = -fPIC -Werror -Wextra -O2
#Linking flags
LDFLAGS = -shared
#Sources
SOURCES = libcomponent.c
#Used to make sure we recompile c files when h-file is changed
OBJ = libcomponent.o
#Lib
TARGET = libcomponent.so
#Installation directory
DESTDIR = .
#Test
TESTFLAGS = -Wall
TESTDIR = $(CURPATH)
TESTSOURCES = componentTest.c
TESTOBJ = componentTest.o
TESTTARGET = componentTest
LIB_DIR = $(CURPATH)
LD = -L$(CURDIR) -l$(CURDIR)/libcomponent.so

all: $(TARGET)

#Object file depends on c files which depends on h-files
libcomonent.o: libcomponent.c component.h

#To generate the o-file make needs to compile the c-files using
#compiler stated in CC makro. $@ says that the compilation output
#should be put in filename stated on the left hand of the ":" on
#row below. The $< is the source file
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(CFLAGS)

test: $(TESTDIR)$(TESTTARGET)

$(TESTDIR)$(TESTOBJ): $(TESTDIR)$(TESTSOURCES)
	$(CC) -c -o $@ $< $(TESTFLAGS) $(LD)

$(TESTDIR)$(TESTTARGET): $(TESTDIR)$(TESTOBJ)
	$(CC) -o $@ $^ $(TESTFLAGS) $(LD)

check:
	$(TESTDIR)$(TESTTARGET)

install: $(TARGET)
	cp $< $(DESTDIR)$(TARGET)

uninstall:
	rm -f $(DESTDIR)$(TARGET)

clean:
	$(RM) $(TARGET) *.o *~
	$(RM) $(TESTDIR)$(TESTTARGET) $(TESTDIR)*.o $(TESTDIR)*~
