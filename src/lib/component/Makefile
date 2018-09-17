#Compilator to use
CC=gcc
#FLags to show all warnings
CFLAGS = -fPIC -Werror -Wextra -O2
#Linking flags
LDFLAGS = -shared
#Sources
SOURCES = component.c
#Used to make sure we recompile c files when h-file is changed
OBJ = component.o
#Lib
TARGET = libcomponent.so
#Installation directory
DESTDIR = /usr/local/src/linuxkurs/electrotest/src/component

all: $(TARGET)

#Object file depends on c files which depends on h-files
comonent.o: component.c component.h

#To generate the o-file make needs to compile the c-files using
#compiler stated in CC makro. $@ says that the compilation output
#should be put in filename stated on the left hand of the ":" on
#row below. The $< is the source file
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(CFLAGS)

install: $(TARGET)
	cp $< $(DESTDIR)$(TARGET)

uninstall:
	rm -f $(DESTDIR)$(TARGET)

clean:
	$(RM) $(TARGET) *.o *~
