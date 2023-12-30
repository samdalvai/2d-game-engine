#include "Game.h"
#include "Logger.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>

Game::Game() {
    isRunning = false;
    Logger::log("Game constructor called");
}

Game::~Game() {
    Logger::log("Game destructor called");
}

void Game::initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Logger::err("Error initializing SDL");
        return;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    // Use a fixed width and height to force the number of pixels regardles of the screen size
    windowWidth = 800;//displayMode.w;
    windowHeight = 600;//displayMode.h;

    window = SDL_CreateWindow(
        NULL, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        windowWidth, 
        windowHeight,
        SDL_WINDOW_BORDERLESS
    );

    if (!window) {
        Logger::err("Error creating SDL window");
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        Logger::err("Error creating SDL renderer");
        return;
    }

    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    isRunning = true;
}

void Game::run() {
    setup();
    while (isRunning) {
        processInput();
        update();
        render();
    }
}

void Game::processInput() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
            break;
        default:
            break;
        }
    }
}

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::setup() {
    // TODO: set up initial objects
    playerPosition = glm::vec2(10.0, 20.0);
    playerVelocity = glm::vec2(100.0, 0);
}

void Game::update() {
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecondsPreviousFrame);

    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    double deltaTime = (SDL_GetTicks() - millisecondsPreviousFrame) / 1000.0f;

    millisecondsPreviousFrame = SDL_GetTicks();
    
    playerPosition.x += playerVelocity.x * deltaTime;
    playerPosition.y += playerVelocity.y * deltaTime;
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    //TODO: render all game objects
    SDL_Surface* surface = IMG_Load("./assets/images/tank-panther-right.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Destination rectangle
    SDL_Rect destRect = {
        static_cast<int>(playerPosition.x), 
        static_cast<int>(playerPosition.y),
        32,
        32
    };

    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
}

void Game::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}