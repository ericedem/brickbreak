#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Game.hpp"

void Game::start(void) {
    if(_gameState != Uninitialized) {
        return;
    }

    bool initialized = init();
    if (!initialized) return;

    while(_gameState != Game::Exiting) {
        gameLoop();
    }

    close();
};

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

    _window = SDL_CreateWindow("Game",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if( _window == NULL ) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // load support for the JPG and PNG image formats
    int flags=IMG_INIT_JPG|IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if((initted&flags) != flags) {
        printf("IMG_Init: Failed to init required png support! SDL Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
};

void Game::gameLoop() {
    SDL_Event e;

    //Handle events on queue
    while( SDL_PollEvent( &e ) != 0 ) {
        if(e.type == SDL_QUIT) {
            _gameState = Game::Exiting;
        }
    }
};

void Game::close() {
    //Destroy window
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    _renderer = NULL;
    _window = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

Game::GameState Game::_gameState = Uninitialized;
SDL_Window* Game::_window = NULL;
SDL_Renderer* Game::_renderer = NULL;
