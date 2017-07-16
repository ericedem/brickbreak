#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class Game {
public:
    static void start();

private:
    static bool init();
    static void gameLoop(double tdelta);
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
