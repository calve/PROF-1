#Options et macros globales à la compilation
DEMDEBUG=yes
CC=gcc
OPTIONS=-Wall -W
OBJECTS=src/*.o

#Chemin de fichiers sources + objets
DEMANDE=src/demande.c
DEMANDEO = src/demande.o
SUPPR=src/suppr.c
SUPPRO=src/suppr.o
STRUCTSTR=src/structStr.c
STRUCTSTRO=src/structStr.o
PARSE=src/parse.c
PARSEO=src/parse.o
MAIN=src/main.c

#Chemin du binaire
PROF=bin/prof

#Linkers
CURLLINK=-lcurl
ZLIBLINK=-lzip
READLINELINK=-lreadline

#Ajout du mode débuggage de GCC s'il est activé
ifeq ($(DEMDEBUG),yes)
	OPTIONS+= -g
endif

#Directive de compilation globale
all: demande suppr structstr parse main
ifeq ($(DEMDEBUG),yes)
	@echo "Génération en mode debug"
endif

#Directives de compilation
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

#Directives de nettoyage
cleanall: cleanobj cleanprg

cleanobj:
	rm $(OBJECTS)

cleanprg:
	rm $(PROF)
