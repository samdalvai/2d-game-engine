#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

class Game {
    private:
        bool isRunning;
        int millisecondsPreviousFrame;
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        Game();
        ~Game();
        void initialize();
        void run();
        void processInput();
        void setup();
        void update();
        void render();
        void destroy();

        int windowWidth;
        int windowHeight;
};

#endif