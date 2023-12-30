#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game {
    private:
        bool isRunning;
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        Game();
        ~Game();
        void initialize();
        void run();
        void setup();
        void processInput();
        void update();
        void render();
        void destroy();

        int windowWidth;
        int windowHeight;
};

#endif