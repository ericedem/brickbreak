#ifndef Ball_hpp
#define Ball_hpp

class Ball {
  public:
    Ball();
    void draw(SDL_Renderer* renderer);

    void move(double time_delta);

  private:
    // Scalar velocity
    double vel;
    double x;
    double y;
    double radius;
};

#endif
