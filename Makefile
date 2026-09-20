CC = gcc
CFLAGS_BASE = -Wall -pthread
CFLAGS_O0 = $(CFLAGS_BASE) -O0
CFLAGS_O3 = $(CFLAGS_BASE) -O3

all: varredura_linha varredura_coluna padrao_O0 padrao_O3 bloco_O0 bloco_O3 matmul_pthreads matmul_pthreads_bloco

varredura_linha: varredura_linha.c
	$(CC) $(CFLAGS_O3) -o $@ $<

varredura_coluna: varredura_coluna.c
	$(CC) $(CFLAGS_O3) -o $@ $<

padrao_O0: matmul_padrao.c
	$(CC) $(CFLAGS_O0) -o $@ $<

padrao_O3: matmul_padrao.c
	$(CC) $(CFLAGS_O3) -o $@ $<

bloco_O0: matmul_bloco.c
	$(CC) $(CFLAGS_O0) -o $@ $<

bloco_O3: matmul_bloco.c
	$(CC) $(CFLAGS_O3) -o $@ $<

matmul_pthreads: matmul_pthreads.c
	$(CC) $(CFLAGS_O3) -o $@ $<

matmul_pthreads_bloco: matmul_pthreads_bloco.c
	$(CC) $(CFLAGS_O3) -o $@ $<

clean:
	rm -f varredura_linha varredura_coluna padrao_O0 padrao_O3 bloco_O0 bloco_O3 matmul_pthreads matmul_pthreads_bloco
