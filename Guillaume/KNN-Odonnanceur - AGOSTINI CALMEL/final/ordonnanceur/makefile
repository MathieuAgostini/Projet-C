CC=gcc
CFLAGS= -Wall #-fsanitize=address
LDFLAGS= #-fsanitize=address
EXEC=ORDONNANCEUR
BINARYPATH=bin/
SRC= $(wildcard *.c)
OBJ= $(addprefix $(BINARYPATH), $(SRC:c=o))

FICHIERS_COMPLEMENTAIRES=OrdonnanceurLogs.txt
VERSIONS=$(sort $(wildcard [0-9]*.x))
ifdef VERSIONS
NOUVELLEVERSION=$$(($(basename $(lastword $(VERSIONS)))+1)).x
else
NOUVELLEVERSION=1.x
endif

all: $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BINARYPATH)%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)

	

.PHONY: clean mrproper nouvelleVersion

clean:
		rm -rf $(BINARYPATH)*.o
		
mrproper: clean
		rm -rf $(EXEC)

nouvelleVersion:
	@$(MAKE)
	@mkdir $(NOUVELLEVERSION)
	@cp *.c *.h readme $(EXEC) $(FICHIERS_COMPLEMENTAIRES) -t $(NOUVELLEVERSION)
	@fillCTemplate --newVersion $(NOUVELLEVERSION)
	@mv $(NOUVELLEVERSION)/$(EXEC) $(NOUVELLEVERSION)/$(basename $(NOUVELLEVERSION)).0
	@echo "________________________________________________________________"
	@echo "Creation de la version $(NOUVELLEVERSION) terminée."