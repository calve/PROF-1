DEMDEBUG=yes
CC=gcc
MAIN=src/main.c
PROF=bin/prof
OPTIONS=-Wall -W
CURLLINK=-lcurl
ZLIBLINK=-lzip

ifeq ($(DEMDEBUG),yes)
	OPTIONS+= -g
endif

all: main
ifeq ($(DEMDEBUG),yes)
	@echo "Génération en mode debug"
endif

main: $(MAIN)
ifeq ($(DEMDEBUG),yes)
	$(CC) -DNDEBUG $(OPTIONS) $(MAIN) $(ZLIBLINK) $(CURLLINK) -v -o $(PROF)
else
	$(CC) $(OPTIONS) $(MAIN) $(CURLLINK) -o prof
endif

cleanall: cleanobj cleanprg

cleanobj:
	rm *.o

cleanprg:
	rm prof
