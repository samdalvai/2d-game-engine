build:
	g++ -Wall -std=c++17 -I"./libs" src/*.cpp src/**/*.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -llua -o gameengine;

run:
	./gameengine

clean:
	rm gameengine