compile:
	@g++ main.cpp ui.cpp fractal.cpp -Wall -pedantic -Wextra -Werror -lsfml-graphics -lsfml-window -lsfml-system -lpthread -o main

run:
	@./main

clean:
	@rm -f main

all:
	@make clean
	@make compile
	@make run
