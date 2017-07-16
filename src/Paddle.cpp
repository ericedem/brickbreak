#include "Paddle.hpp"
#include <stdio.h>

Paddle::Paddle() : width(64), height(16), x(500), y(0), xvel(0), maxvel(240) {}

void Paddle::draw(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  static SDL_Rect rect;

  rect.x = x;
  rect.y = y;
  rect.w = width;
  rect.h = height;
  SDL_RenderDrawRect(renderer, &rect);
}

void Paddle::go_right() {
  xvel = maxvel;
}

void Paddle::go_left() {
  xvel = -maxvel;
}

void Paddle::stop() {
  xvel = 0;
}

/*
The general collision behavior for the paddle is that it will stop moving and
restrict itself to within the boundary.
*/
void Paddle::collideLeft(float bound) {
  if (x < bound) {
    xvel = 0;
    x = bound;
  }
}

void Paddle::collideRight(float bound) {
  if (x + width > bound) {
    xvel = 0;
    x = bound - width;
  }
}

void Paddle::move(double time_delta) {
  x += xvel * time_delta;
}
