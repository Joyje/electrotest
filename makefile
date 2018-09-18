CC = gcc
CFLAGS = -Wall
RM= rm -rf

#Directory names
SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
TMP_DIR = tmp

#Paths to all files
SRC := $(shell find $(SRC_DIR) -name '*.c') 
OBJ := $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
OBJFILES = $(notdir $(OBJ)) 
LIBOBJFILES = $(filter lib%,$(OBJFILES))
SRCOBJ = $(filter-out $(OBJ_DIR)/lib%.o,$(OBJ))
LIBOBJ = $(filter $(foreach i,$(LIBOBJFILES),%$(i)),$(OBJ))
DEPS = $(OBJ:%.o=%.d) 
LIB = $(LIBOBJ:$(OBJ_DIR)/lib%.o=$(LIB_DIR)%.so)
LIBFILES = $(notdir $(LIB))

LD = $(dir $(LIB:%=-L%)) $(LIBFILES:lib%.so=-l%) $(dir $(LIB:%=-Wl,-rpath=%))
MAIN = electrotest

all:	$(MAIN)
	@echo '$(MAIN) compiled. Type "sudo make install" to install.' 

$(MAIN): $(SRCOBJ) $(LIB)
	$(CC) $(CFLAGS) $(SRCOBJ) -o $@ $(LD)

$(SRCOBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

lib: $(LIB)

$(LIB): $(LIB_DIR)%.so: $(OBJ_DIR)/lib%.o
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -shared -fPIC $< -o $@

$(LIBOBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c -fPIC $< -o $@

-include $(DEPS) 

.PHONY: clean install uninstall

clean:
	$(RM) $(SRCOBJ) $(LIBOBJ) $(DEPS) $(OBJ_DIR)

install:
	cp $(MAIN) /usr/local/bin/ 
	cp $(LIB) /usr/local/lib/

uninstall:
	$(RM) /usr/local/bin/$(MAIN)
	$(foreach i,$(LIBFILES),$(RM) /usr/local/lib/$(i))
