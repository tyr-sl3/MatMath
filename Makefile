CC=clang++-3.6
EXEC=matmath
#FLAGS=-std=c++1y -Wall -pedantic -Wextra -Werror
FLAGS=-std=c++14 -Wall -Wextra -Werror -pedantic-errors \
			-Wold-style-cast -Woverloaded-virtual -Wfloat-equal \
			-Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align \
			-Wconversion -Wshadow -Weffc++ -Wredundant-decls \
			-Winit-self -Wswitch-default -Wswitch-enum -Wundef \
			-Winline -Wunused -Wuninitialized
SRC=example.cc

all: debug
	
debug:
	@$(CC) $(FLAGS) -g $(SRC) -o $(EXEC)

release:
	@$(CC) $(FLAG) -O2 -DNDEBUG $(SRC) -o $(EXEC)

clean:
	@rm -rf src/*.o src/.*.h.swp src/.*.cc.swp $(EXEC)
