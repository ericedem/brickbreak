//
//  Game.hpp
//  sdl-tutorial
//
//  Created by Eric Edem on 7/8/17.
//  Copyright © 2017 Eric Edem. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class Game {
public:
    static void start();

private:
    static bool init();
    static void gameLoop();
    static void close();
    
    enum GameState {
        Uninitialized,
        Playing,
        Exiting
    };
    
    static GameState _gameState;
    
    static SDL_Window* _window;
    static SDL_Renderer* _renderer;
    
    const static int SCREEN_WIDTH = 1024;
    const static int SCREEN_HEIGHT = 768;
};


#endif /* Game_hpp */
