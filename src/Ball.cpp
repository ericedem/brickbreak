
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

Ball::Ball() : x(500), y(500), radius(10), vel(120), angle(PI/4) {}
Ball::Ball(int x, int y): x(x), y(y), radius(10), vel(120), angle(PI/4) {}
Ball::Ball(int x, int y, double vel, double angle):
  x(x), y(y), vel(vel), angle(angle), radius(10) {}

void Ball::collideBounds(SDL_Rect bounds) {
  if (x - radius < bounds.x) {
    // collide left
    x = bounds.x + radius;
    angle = PI - angle;
  }
  if (x + radius > bounds.x + bounds.w) {
    // collide right
    x = bounds.x + bounds.w - radius;
    angle = PI - angle;
  }
  if (y - radius < bounds.y) {
    // collide top
    y = bounds.y + radius;
    angle = -angle;
  }
  if (y + radius > bounds.y + bounds.h) {
    // collide bottom
    y = bounds.y + bounds.h - radius;
    angle = -angle;
  }
}

void Ball::draw(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  drawCircle(renderer, x, y, radius);
}

// 0 degrees points right
void Ball::move(double time_delta) {
  x += vel * time_delta * cos(angle);
  y += vel * time_delta * sin(angle);
}
