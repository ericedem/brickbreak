
#include <SDL2/SDL.h>
#include "Ball.hpp"


void drawCircle(SDL_Renderer* renderer, int x, int y, int r) {
  for (int w = -r; w < r; w++) {
    for (int h = -r; h < r; h++) {
      if (w*w + h*h < r*r) {
        SDL_RenderDrawPoint(renderer, x + w, y + h);
      }
    }
  }
}

Ball::Ball() : x(500), y(500), radius(10), vel(0) {}

void Ball::draw(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  drawCircle(renderer, x, y, radius);
}
