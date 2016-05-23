CC=clang++
EXEC=matmath
FLAGS=-std=c++1y -Wall -Wextra -Werror -pedantic-errors \
			-Wold-style-cast -Woverloaded-virtual -Wfloat-equal \
			-Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align \
			-Wconversion -Wshadow -Weffc++ -Wredundant-decls \
			-Winit-self -Wswitch-default -Wswitch-enum -Wundef \

all: main.o
	$(CC) -o $(EXEC) $^

main.o: example/main.cc
	$(CC) -o $@ -c $< $(FLAGS)

clean:
	@rm -rf src/*.o src/.*.h.swp src/.*.cc.swp $(EXEC)
