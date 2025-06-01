CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O1 -fno-omit-frame-pointer -g

# Ficheiros fonte
SRC_JOGO = main.c jogo.c
OBJ_JOGO = main.o jogo.o
OUT_JOGO = jogo

SRC_TESTES = testes.c jogo.c
OBJ_TESTES = testes.o jogo.o
OUT_TESTES = testar

# Regra por defeito: compilar apenas o jogo
all: $(OUT_JOGO)

# Compilar jogo
$(OUT_JOGO): $(OBJ_JOGO)
	$(CC) $(CFLAGS) -o $@ $^

# Compilar testes (se o utilizador quiser)
testar: $(OBJ_TESTES)
	$(CC) $(CFLAGS) -o $(OUT_TESTES) $^

# Regras para gerar os .o
main.o: main.c jogo.h
jogo.o: jogo.c jogo.h
testes.o: testes.c jogo.h

# Limpar ficheiros gerados
clean:
	rm -f *.o $(OUT_JOGO) $(OUT_TESTES)
