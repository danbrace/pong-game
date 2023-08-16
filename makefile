
# Builds pong game
pong: main.o game.o
	gcc -g -o $@ $^ -I./lib\SDL2\include -L./lib\SDL2\lib -lSDL2

%.o:%.c *.h
	gcc -std=c99 -pedantic -Wformat -Wreturn-type -g -c $< -o $@