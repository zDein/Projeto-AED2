APPS = ./apps
BIN = ./bin
INCLUDE = ./include
LIB = ./lib
OBJ = ./obj
SRC = ./src

FLAGS = -O3 -Wall
LIBS = -lm -led -L $(LIB)



all: libed myapps


libed:
	gcc -c ./src/test.c  -I ./include -o ./obj/function.o
	ar -rcs ./lib/libed.a ./obj/*.o


myapps: clean_apps
	gcc ./apps/main.c ./obj/function.o -I ./include -o ./bin/app

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(INCLUDE) -o $@

$(BIN)/%: $(APPS)/%.c
	gcc $(FLAGS) $< $(LIBS) -I $(INCLUDE) -o $@



run_teste:
	./bin/app<teste.txt


run:
	./bin/app

clean:
	rm ./bin/* ./obj/* ./lib/*

clean_apps:
	rm -rf ./bin/*




