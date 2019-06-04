all:
	@gcc src/*.c -o bin/game -Wall -Wextra -Wpedantic -Iapp/jni/include `sdl2-config --cflags --libs` -lm -lSDL2_ttf

run:
	bin/game