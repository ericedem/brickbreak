#include "Paddle.hpp"
#include <stdio.h>

Paddle::Paddle() : width(64), height(16), x(500), y(0), xvel(0), maxvel(120) {}

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

void Paddle::move(double time_delta) {
  x += xvel * time_delta;
}
