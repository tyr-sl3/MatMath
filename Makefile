CC=clang++
EXEC=matmath
FLAGS=-std=c++1y -Wall -Wextra -Werror -pedantic-errors -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline -Wunused -Wuninitialized
SRC=main.cc

all: debug
	
debug:
	@$(CC) $(FLAGS) -g $(SRC) -o $(EXEC)

release:
	@$(CC) $(FLAG) -O2 -DNDEBUG $(SRC) -o $(EXEC)

clean:
	@rm -rf *.o .*.h.swp .*.cc.swp $(EXEC)
