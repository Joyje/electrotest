# Vi börjar med att definera några basvariabler så som koplitator, namn på vårt
# program, etc.

CC = gcc
CFLAGS = -Wall
RM = rm -rf
MAIN = electrotest


# Här namnges alla kataloger i vår katalogstruktur

SRC_DIR = src/
OBJ_DIR = obj/
LIB_DIR = lib/
TMP_DIR = tmp/


# Nedan anger vi alla filer vi tänker jobba med:

SRC := $(shell find $(SRC_DIR) -name '*.c') # Rekursiv sökning för att hitta .c filer under source katalogen och dess underkataloger.
OBJ := $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o) # Alla sourcefiler får en motsvarande objektfil i objektkatalogen.
OBJFILES = $(notdir $(OBJ)) # Namnen på alla objektfiler utan sökvägen.
LIBOBJFILES = $(filter lib%,$(OBJFILES)) # Filtrera ut alla objektfiler som har "lib" någonstans i filnamnet.
LIBFILES = $(LIBOBJFILES:%.o=%.so) # De utfiltrerade filerna får en motsvarande biblioteksfil (.so).
SRCOBJ = $(filter-out $(LIBOBJ) $(OBJ_DIR)$(LIB_DIR)%,$(OBJ)) # Filtrera ut alla objektfiler som inte ska bli bibliotek.
LIBOBJ = $(filter $(foreach i,$(LIBOBJFILES),%$(i)),$(OBJ)) # Samma filer som i LIBOBJFILES fast med sökvägarna.
DEPS = $(OBJ:%.o=%.d) # Objektfilerna får dependencyfiler (.d).
LIB = $(LIBOBJ:$(OBJ_DIR)$(LIB_DIR)%.o=$(LIB_DIR)%.so) # Samma som LIBFILES fast med sökväg.


# Nedan specifceras alla argument som kompilatorn behöver för att programmet vi
# gör skall använda de olika biblioteken vi vill ha med. Flaggan -L visar vilka
# kataloger biblioteken ligger i så att kompilatorn kan hitta dem. Samtliga
# kataloger läggs till med hjälp av en foreach loop. -l flaggan används för att
# specificera själva biblioteken vi skall använda. Filnamnen anges då utan "lib"
# och ".so". Flaggan -Wl,-rpath= lägger till de specificerade sökvägarna till
# programmets RPATH. Sökvägarna till våra bibliotek läggs till med en foreach
# loop, så kompilatorn ser till att de hamnar i programmets RPATH. Detta gör
# programmet körbart även fast vi inte flyttat biblioteken till någon av linux
# standard lib kataloger.

LD = $(foreach i,$(dir $(LIB)),-L$(i)) $(LIBFILES:lib%.so=-l%) $(foreach i,$(dir $(LIB)),-Wl,-rpath=$(i)) -lm


# Nu när alla variabler har specificerats skriver vi alla operationer som skall
# utföras och i vilken ordning:

# Gör allt! (standard):
all:	$(MAIN)
	@echo '$(MAIN) compiled. Type "sudo make install" to install.' 

# Bygg exekverbara filen som angesi $(MAIN) med de objektfiler och bibliotek
# som anges i $(SRCOBJ) och  $(LIB)
# -o flaggan är bygg resultatet.
# S@ säger att resultatet av kompilatet ska skrivas till den fil som anges
# längs till vänster på raden ovanför.
$(MAIN): $(SRCOBJ) $(LIB)
	$(CC) $(CFLAGS) $(SRCOBJ) -o $@ $(LD)

# Objektfilen byggs och baseras på c filen
# -MMD Skapar en regel som beskriver vilka beorende källkodsfilen har
# -c kompilerar källkoden utan att länka
# $< är källkodsfilen
# -o flaggan är bygg resultatet
# S@ säger att resultatet av kompilatet ska skrivas till den fil som anges
# längs till vänster på raden ovanför
$(SRCOBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

# Gör bibliotek:
lib: $(LIB)

# -shared är att ett dynamiskt bibliotek ska skapas
# -fPIC Position oberoende kod. Den genererade maskin koden är inte beroende
# av att finnas på en specifik adress. Detta används för dynamiska bibliotek
# som flyttas till andra adresser i minnet.
$(LIB): $(LIB_DIR)%.so: $(OBJ_DIR)$(LIB_DIR)%.o
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -shared -fPIC $< -o $@

$(LIBOBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c -fPIC $< -o $@

-include $(DEPS)

.PHONY: clean install uninstall

# Ta bort objektfiler (.o) och dependencyfiler (.d) samt deras katalog:
clean:
	$(RM) $(SRCOBJ) $(LIBOBJ) $(DEPS) $(OBJ_DIR)

# Kopiera programmet och biblioteken till systemets standardplatser så de hittas
# av systemets olika *PATH variabler:
install:
	cp $(MAIN) /usr/local/bin/ 
	cp $(LIB) /usr/local/lib/

# Ta bort de filer vi kopierat till systemets standardplatser:
uninstall:
	$(RM) /usr/local/bin/$(MAIN)
	$(foreach i,$(LIBFILES),$(RM) /usr/local/lib/$(i))
