MAIN = src/main.c
OPTIONS = -Wall -Werror -pedantic
CURLLINK = -lcurl

all: main

main: $(MAIN)
	gcc $(OPTIONS) $(MAIN) $(CURLLINK) -o prof

clean:
	rm *.o
