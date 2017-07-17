#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <chrono>
#include <sstream>
#include <iostream>

#include "Game.hpp"
#include "Ball.hpp"
#include "Paddle.hpp"

typedef std::chrono::steady_clock Clock;

void renderFPS(SDL_Renderer * renderer, double fps) {
    // TODO: this should be loaded once
    TTF_Font* font = TTF_OpenFont("fonts/OpenSans-Regular.ttf", 24);
    if(!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return;
    }
    SDL_Color White = {255, 255, 255, 0};
    const char * text = std::to_string(fps).c_str();
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(
        renderer, surfaceMessage);
    SDL_Rect Message_rect = {0, 0, 100, 100};
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    // Free memory
    TTF_CloseFont(font);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}

void Game::start(void) {
    if(_gameState != Uninitialized) {
        return;
    }

    bool initialized = init();
    if (!initialized) return;

    Clock::time_point last_time = Clock::now();
    Clock::time_point current_time = Clock::now();
    Clock::duration time_span;
    double tdelta;

    while(_gameState != Game::Exiting) {
        // Manage time so that the loop can focus on logic
        last_time = current_time;
        current_time = Clock::now();
        time_span = current_time - last_time;
        tdelta = double(time_span.count()) * Clock::period::num / Clock::period::den;

        gameLoop(tdelta);
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

    // TODO: Make vsync optional
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // load support for the JPG and PNG image formats
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init (flags);
    if((initted & flags) != flags) {
        printf("IMG_Init: Failed to init required png support! SDL Error: %s\n", IMG_GetError());
        return false;
    }

    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        return false;
    }

    return true;
};

void Game::gameLoop(double tdelta) {
    static SDL_Event event;

    // TODO: textures / sizes etc. should probably all be defined at this level
    static Paddle p = Paddle(SCREEN_WIDTH/2, SCREEN_HEIGHT-16);
    static Ball b = Ball(SCREEN_WIDTH/2, SCREEN_HEIGHT-30, 120, -PI/4);

    static bool left_pressed = false;
    static bool right_pressed = false;

    // -- Handle Control logic -------------------------------------------------
    while( SDL_PollEvent( &event ) != 0 ) {
        switch(event.type) {
            case SDL_QUIT:
                _gameState = Game::Exiting;
                break;
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        left_pressed = true;
                        break;
                    case SDLK_RIGHT:
                        right_pressed = true;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        left_pressed = false;
                        break;
                    case SDLK_RIGHT:
                        right_pressed = false;
                        break;
                }
                break;
        }
    }

    if (left_pressed && right_pressed) {
        p.stop();
    } else if (left_pressed) {
        p.go_left();
    } else if (right_pressed) {
        p.go_right();
    } else {
        p.stop();
    }

    // -- Position Updates -----------------------------------------------------
    p.move(tdelta);
    b.move(tdelta);

    // -- Collision Detection --------------------------------------------------
    // TODO: make this a constant somewhere
    static SDL_Rect bounds = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    p.collideRight(SCREEN_WIDTH);
    p.collideLeft(0);
    b.collideBounds(bounds);

    // -- Drawing --------------------------------------------------------------
    // Clear window to black
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_RenderClear(_renderer);

    p.draw(_renderer);
    b.draw(_renderer);

    // TODO: this rendering should be optional.
    renderFPS(_renderer, 1.0/tdelta);

    // Paint the screen baby
    SDL_RenderPresent(_renderer);
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
