//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
// #include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include "Game.hpp"

//Screen dimension constants
// const int SCREEN_WIDTH = 640;
// const int SCREEN_HEIGHT = 480;

// // TODO: Figure out where to put these.
// //SDL_Window* window = NULL;
// //SDL_Renderer* renderer = NULL;

// bool init(SDL_Window* &window, SDL_Renderer* &renderer) {
//     if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
//         SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
//         return false;
//     }

//     // TODO: Is this the right thing here?
//     if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
//         printf( "Warning: Linear texture filtering not enabled!" );
//     }

//     window = SDL_CreateWindow("Game",
//                               SDL_WINDOWPOS_UNDEFINED,
//                               SDL_WINDOWPOS_UNDEFINED,
//                               SCREEN_WIDTH,
//                               SCREEN_HEIGHT,
//                               SDL_WINDOW_SHOWN);
//     if( window == NULL ) {
//         printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
//         return false;
//     }

//     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//     if (renderer == NULL) {
//         printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
//         return false;
//     }

//     SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

//     // load support for the JPG and PNG image formats
//     int flags=IMG_INIT_JPG|IMG_INIT_PNG;
//     int initted=IMG_Init(flags);
//     if((initted&flags) != flags) {
//         printf("IMG_Init: Failed to init required png support! SDL Error: %s\n", IMG_GetError());
//         return false;
//     }

//     return true;
// };

// void close(SDL_Window* &window, SDL_Renderer* &renderer) {

//     // Free images?

//     //Destroy window
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     renderer = NULL;
//     window = NULL;

//     //Quit SDL subsystems
//     IMG_Quit();
//     SDL_Quit();
// };

#include <stdio.h>
int main( int argc, const char* argv[] )
{
    Game::start();
    return 0;
//    SDL_Window* window = NULL;
//    SDL_Renderer* renderer = NULL;
//
//    bool initialized = init(window, renderer);
//    if (!initialized) {
//        close(window, renderer);
//        return 1;
//    }
//
//    SDL_Surface* surface = IMG_Load("images/Small-soldier.png");
//
//    //Event handler
//    SDL_Event e;
//    bool running = true;
//
//    while(running) {
//        //Handle events on queue
//        while( SDL_PollEvent( &e ) != 0 ) {
//            if(e.type == SDL_QUIT) {
//                running = false;
//            }
//        }
//    }
//
//    close(window, renderer);
//
//    return 0;
}
