CC = gcc
CFLAGS = -Wall
RM= rm -rf

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
TMP_DIR = tmp

SRC := $(shell find $(SRC_DIR) -name '*.c') 
OBJ := $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
SRCOBJ = $(filter-out $(OBJ_DIR)/lib%.o,$(OBJ))
LIBOBJ = $(filter $(OBJ_DIR)/lib%.o,$(OBJ))
DEPS = $(OBJ:%.o=%.d) 
LIB = $(LIBOBJ:$(OBJ_DIR)/lib%.o=$(LIB_DIR)%.so)

LD = -L$(LIB_DIR) $(LIB:lib/lib%.so=-l%) -Wl,-rpath=$(LIB_DIR)
MAIN = electrotest

all:	$(MAIN) 
	@echo '$(MAIN) compiled. Type "sudo make install" to install.' 

$(MAIN): $(SRCOBJ) $(LIB)
	$(CC) $(CFLAGS) $^ -o $@ $(LD)

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
	$(RM) /usr/local/lib/$(LIB:$(LIB_DIR)%.so=%.so)
