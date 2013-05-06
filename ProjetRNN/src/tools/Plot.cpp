#include "Plot.hpp"
#include <algorithm>

Plot::Plot(int nb_curve)
{    
  _nb_curve = nb_curve;
  array_plot = new std::deque<float>[_nb_curve];
  colors = new SDL_Color[_nb_curve];
  for (int i=0;i<_nb_curve;i++)
    {
      array_plot[i].assign(400, 0);
    }
  
  int range = 255/_nb_curve;
  std::vector<int> v(_nb_curve, 0);
  for (int i=0;i<_nb_curve;i++) {
    v.at(i) = i*range; }
  random_shuffle(v.begin(), v.end());
  for (int i=0;i<_nb_curve;i++) {
    colors[i].r = v[i];}
  random_shuffle(v.begin(), v.end());
  for (int i=0;i<_nb_curve;i++) {
    colors[i].g = v[i];}
  random_shuffle(v.begin(), v.end());
  for (int i=0;i<_nb_curve;i++) {
    colors[i].b = v[i];}
     
  SDL_Init(SDL_INIT_VIDEO);
  _screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE);
  _background = SDL_LoadBMP("src/tools/background2.bmp");

  apply_surface(600, 0, _background, _screen);
  SDL_SetPalette(_screen, SDL_LOGPAL|SDL_PHYSPAL, colors, 0, 256);
}

//void Plot::createColors(

void Plot::push(int i, float value)
{
  array_plot[i].pop_front();
  array_plot[i].push_back(value);  
}

void Plot::update(int h)
{
  events();
  DrawScreen(_screen, h);
}

void Plot::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(source, NULL, destination, &offset);
}



void Plot::events()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
    {
      switch (event.type)
	{
	case SDL_QUIT:
	  SDL_Quit();
	  exit(0);
	case SDL_KEYDOWN:
	  if (event.key.keysym.sym == SDLK_ESCAPE) {
	    SDL_Quit();
	    exit(0); }
	  break;
	}
    } 
}

void Plot::setpixel(SDL_Surface *screen, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
  Uint32 *pixmem32;
  Uint32 colour;  
 
  colour = SDL_MapRGB( screen->format, r, g, b );
  
  pixmem32 = (Uint32*) screen->pixels  + y + x;
  *pixmem32 = colour;
}

void Plot::DrawScreen(SDL_Surface* screen, int h)
{ 
  int y, ytimesw;
  int x = 700;
  if(SDL_MUSTLOCK(screen)) 
    {
      if(SDL_LockSurface(screen) < 0) return;
    }

  apply_surface(600, 0, _background, _screen);
  
  for (int i = 0; i < array_plot[0].size();i++)
    {      
      for (int j = 0; j<_nb_curve; j++) 
	{
	  y = (int)(500-(array_plot[j].at(i))*400);
	  for (int w = -1; w < 1; w++) {
	    ytimesw = (y+w)*screen->pitch/BPP;
	    //setpixel(screen, x, ytimesw, 0, 0, 0);
	    setpixel(screen, x, ytimesw, colors[j].r, colors[j].g, colors[j].b);
	  }
	}
      x++;
    }
  

  if(SDL_MUSTLOCK(_screen)) SDL_UnlockSurface(_screen);
  
  SDL_Flip(_screen); 
}
