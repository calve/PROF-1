DEMDEBUG=yes
CC=gcc
DEMANDE=src/demande.c
DEMANDEO = src/demande.o
SUPPR=src/suppr.c
SUPPRO=src/suppr.o
MAIN=src/main.c
PROF=bin/prof
OPTIONS=-Wall -W
CURLLINK=-lcurl
ZLIBLINK=-lzip
OBJECTS=src/*.o

ifeq ($(DEMDEBUG),yes)
	OPTIONS+= -g
endif

all: demande suppr main
ifeq ($(DEMDEBUG),yes)
	@echo "Génération en mode debug"
endif

demande: $(DEMANDE)
	$(CC) -DNDEBUG $(OPTIONS) -c $(DEMANDE) -o $(DEMANDEO)

suppr: $(SUPPR)
	$(CC) -DNDEBUG $(OPTIONS) -c $(SUPPR) -o $(SUPPRO)

main: $(MAIN)
ifeq ($(DEMDEBUG),yes)
	$(CC) -DNDEBUG $(OPTIONS) $(DEMANDEO) $(SUPPRO) $(MAIN) $(ZLIBLINK) $(CURLLINK) -v -o $(PROF)
else
	$(CC) $(OPTIONS) $(DEMANDEO) $(SUPPRO) $(MAIN) $(ZLIBLINK) $(CURLLINK) -o $(PROF)
endif

cleanall: cleanobj cleanprg

cleanobj:
	rm $(OBJECTS)

cleanprg:
	rm $(PROF)
