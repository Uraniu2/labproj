CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O1 -fno-omit-frame-pointer -g
SRC = main.c jogo.c
OUT = jogo

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)

#CFLAGS = -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g
#
#all: jogo testar
#
#jogo: main.o jogo.o
#	$(CC) $(CFLAGS) -o jogo main.o jogo.o
#
#testar: testes.o jogo.o
#	$(CC) $(CFLAGS) -o testar testes.o jogo.o
#
#main.o: main.c jogo.h
#jogo.o: jogo.c jogo.h
#testes.o: testes.c jogo.h
#
#clean:
#	rm -f *.o jogo testar