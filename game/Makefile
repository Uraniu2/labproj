CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O1 -fno-omit-frame-pointer -g
SRC = main.c jogo.c
OUT = jogo

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
