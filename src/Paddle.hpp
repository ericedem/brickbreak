#ifndef Paddle_hpp
#define Paddle_hpp

#include <SDL2/SDL.h>

class Paddle {
public:
  Paddle();
  void draw(SDL_Renderer* renderer);
  void go_left();
  void go_right();
  void move(double time_delta);
  void stop();

private:
  double x;
  double y;
  double xvel;
  unsigned int width;
  unsigned int height;
  double maxvel;
};

#endif
