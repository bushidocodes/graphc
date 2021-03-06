## Simple C Makefile

## Define compiler and flags
CC=mpicc 
CXX=cc 
CCFLAGS=-g -std=c99 -Wall -lpthread -lm

all: build

makeres:
	mkdir -p res

makedist:
	mkdir -p dist

build-generator: makedist
	$(CC) ./src/generategraph.c -o ./dist/generategraph.out $(CCFLAGS)

build-bfs: makedist
	$(CC) ./src/main.c -o ./dist/bfs.out $(CCFLAGS)

build: build-bfs

run-generator: build-generator makeres
	./dist/generategraph.out 8 16

run-bfs: build-bfs
	mpirun -n 2 ./dist/bfs.out --mca orte_base_help_aggregate 0

run: run-generator run-bfs

clean: 
	rm -f ./dist/*