DEMDEBUG=yes
CC=gcc
MAIN=src/main.c
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
	$(CC) -DNDEBUG $(OPTIONS) $(MAIN) $(ZLIBLINK) $(CURLLINK) -o prof
else
	$(CC) $(OPTIONS) $(MAIN) $(CURLLINK) -o prof
endif

cleanall: cleanobj cleanprg

cleanobj:
	rm *.o

cleanprg:
	rm prof
