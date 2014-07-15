DEMDEBUG=yes
CC=gcc

DEMANDE=src/demande.c
DEMANDEO = src/demande.o

SUPPR=src/suppr.c
SUPPRO=src/suppr.o

STRUCTSTR=src/structStr.c
STRUCTSTRO=src/structStr.o

PARSE=src/parse.c
PARSEO=src/parse.o

MAIN=src/main.c

PROF=bin/prof
OPTIONS=-Wall -W
CURLLINK=-lcurl
ZLIBLINK=-lzip
READLINELINK=-lreadline
OBJECTS=src/*.o

ifeq ($(DEMDEBUG),yes)
	OPTIONS+= -g
endif

all: demande suppr structstr parse main
ifeq ($(DEMDEBUG),yes)
	@echo "Génération en mode debug"
endif

demande: $(DEMANDE)
	$(CC) -DNDEBUG $(OPTIONS) -c $(DEMANDE) -o $(DEMANDEO)

suppr: $(SUPPR)
	$(CC) -DNDEBUG $(OPTIONS) -c $(SUPPR) -o $(SUPPRO)

structstr: $(STRUCTSTR)
	$(CC) -DNDEBUG $(OPTIONS) -c $(STRUCTSTR) -o $(STRUCTSTRO)

parse: $(PARSE)
	$(CC) -DNDEBUG $(OPTIONS) -c $(PARSE) -o $(PARSEO)

main: $(MAIN)
ifeq ($(DEMDEBUG),yes)
	$(CC) -DNDEBUG $(OPTIONS) $(DEMANDEO) $(SUPPRO) $(STRUCTSTRO) $(PARSEO) $(MAIN) $(ZLIBLINK) $(CURLLINK) $(READLINELINK) -v -o $(PROF)
else
	$(CC) $(OPTIONS) $(DEMANDEO) $(SUPPRO) $(STRUCTSTRO) $(PARSEO) $(MAIN) $(ZLIBLINK) $(CURLLINK) $(READLINELINK) -o $(PROF)
endif

cleanall: cleanobj cleanprg

cleanobj:
	rm $(OBJECTS)

cleanprg:
	rm $(PROF)
