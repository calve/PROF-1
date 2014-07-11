MAIN = src/main.c
OPTIONS = -Wall -Werror -pedantic
CURLLINK = -lcurl

all: main

main: $(MAIN)
	gcc $(OPTIONS) $(MAIN) $(CURLLINK) -o prof

cleanall: cleanobj cleanprg

cleanobj:
	rm *.o

cleanprg:
	rm prof
