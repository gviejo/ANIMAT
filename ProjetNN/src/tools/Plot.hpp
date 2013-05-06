#ifndef PLOT_HH_
#define PLOT_HH_

#include <iostream>
#include "SDL/SDL.h"
#include "smart_ptr.h"
#include "Vector.hpp"
#include <deque>
#define WIDTH 1200
#define HEIGHT 600
#define BPP 4
#define DEPTH 32

class Plot
{
protected:
  int _nb_curve;
  SDL_Surface* _screen;
  SDL_Surface* _background;
  SDL_Color* colors;
  std::deque< float > *array_plot;

public:
  Plot(int nb_curve);
  ~Plot(){
    SDL_FreeSurface(_background);
    SDL_FreeSurface(_screen);
    SDL_Quit();
  }
  void setpixel(SDL_Surface *screen, int x, int y, Uint8 r, Uint8 g, Uint8 b);
  void DrawScreen(SDL_Surface* screen, int h);
  void events();
  void update(int h);
  void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
  
  void push(int i, float value);

};

#endif



