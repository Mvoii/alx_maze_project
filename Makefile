build:
	gcc -Wall -Werror -Wextra -pedantic ./src/*.c -lSDL2 -lSDL2_image -lm -o game

run:
	./game 0x01.map

clean:
	rm game
