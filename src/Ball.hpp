#ifndef Ball_hpp
#define Ball_hpp
#define PI 3.14159

class Ball {
  public:
    Ball();
    Ball(int x, int y);
    Ball(int x, int y, double vel, double angle);
    void collideBounds(SDL_Rect bounds);
    void draw(SDL_Renderer* renderer);

    void move(double time_delta);

  private:
    // Scalar velocity
    double vel;
    double x;
    double y;
    double radius;
    double angle;
};

#endif
