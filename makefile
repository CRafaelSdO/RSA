CC = clang
FLG = -std=c11 -Wall

DBG = $(wildcard DEBUG/*.c)
DBGLB = $(DBG:.c=.h)
SRC = $(wildcard src/*.c)
LIBS = $(wildcard src/libs/*.h)

all: build

build: $(DBG) $(DBGLB) $(SRC) $(LIBS)
	@echo "Compilando Executável..."
	@$(CC) $(FLG) $(DBG) $(SRC) -o $@
	@echo "\tPronto"