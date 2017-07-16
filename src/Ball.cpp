
#include <SDL2/SDL.h>
#include "Ball.hpp"

// TODO: move this to globals somewhere
#define PI 3.14159

void drawCircle(SDL_Renderer* renderer, int x, int y, int r) {
  for (int w = -r; w < r; w++) {
    for (int h = -r; h < r; h++) {
      if (w*w + h*h < r*r) {
        SDL_RenderDrawPoint(renderer, x + w, y + h);
      }
    }
  }
}

Ball::Ball() : x(500), y(500), radius(10), vel(120), angle(PI/4) {}

void Ball::draw(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  drawCircle(renderer, x, y, radius);
}

// 0 degrees points right
void Ball::move(double time_delta) {
  x += vel * time_delta * cos(angle);
  y += vel * time_delta * sin(angle);
}
