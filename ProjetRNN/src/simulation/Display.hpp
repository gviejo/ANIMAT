#ifndef   	DISPLAY_HH_
# define        DISPLAY_HH_

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <valarray>
#include <stdio.h>
#include <unistd.h>

#include "SDL/SDL.h"

#include "Map.hpp"
#include "Robot.hpp"
#include <boost/shared_ptr.hpp>
#include "../tools/smart_ptr.h"

class Display
{
public:
  Display(SPTR<Map> m, SPTR<Robot> r);
  ~Display()
  {
    SDL_FreeSurface(_Map_bmp);
    SDL_FreeSurface(_screen);
    SDL_Quit();
  }    
  void update();
  void update_Map() 
  {
    _blit_Map();
  }

protected:
  SPTR<Map> _Map;
  //const Robot& _Robot;
  SPTR<Robot> _Robot;
  int _w, _h;
  SDL_Surface* _screen, *_Map_bmp;
  SDL_Rect _prev_bb;
  enum status_t { free = 0, obstacle = 255};

  
public:
  void _events();
  void _bb_to_sdl(const Robot::BoundingBox& bb,
		    SDL_Rect *r)
  {
    r->x = (Sint16) _Map->real_to_pixel(bb.x);
    r->y = (Sint16) _Map->real_to_pixel(bb.y);
    r->w = (Sint16) _Map->real_to_pixel(bb.w);
    r->h = (Sint16) _Map->real_to_pixel(bb.h);
  }
  
  void _quit()
  {
    SDL_Quit();
    exit(0);
  }
  void _put_pixel(SDL_Surface* surf,
		  Uint32 color, unsigned x, unsigned y)
  {
    if (x >= surf->w || x < 0 || y >= surf->h || y < 0)
      return;
    Uint32 *bufp = (Uint32*)surf->pixels  + y * surf->pitch / 4 + x;
    *bufp = color;
  }
  void _put_pixel(SDL_Surface* surf,
		  unsigned x, unsigned y,
		  Uint8 r, Uint8 g, Uint8 b)
  {  _put_pixel(surf, SDL_MapRGB(surf->format, r, g, b), x, y); }
  
  void _blit_Map();

  // used by _circle
  void _circle_points(SDL_Surface* surf,
		      int cx, int cy, int x, int y, Uint32 color);
  void _circle(SDL_Surface* surf,
	       int x_center, int y_center, int radius,
	       Uint8 r, Uint8 g, Uint8 b)
  { _circle(surf, x_center, y_center, radius, SDL_MapRGB(surf->format, r, g, b)); }
  void _circle(SDL_Surface* surf,
	       int x_center, int y_center, int radius,
	       Uint32 color);
  //
  void _disc(SDL_Surface* surf,
	       int x_center, int y_center, int radius,
	       Uint8 r, Uint8 g, Uint8 b)
  { _disc(surf, x_center, y_center, radius, SDL_MapRGB(surf->format, r, g, b)); }
  void _disc(SDL_Surface* surf,
	     int x_center, int y_center, int radius,
	     Uint32 color);
  //
  void _line(SDL_Surface* surf, int x0, int y0, int x1, int y1, 
	     Uint8 r, Uint8 g, Uint8 b)
  { _line(surf, x0, y0, x1, y1, SDL_MapRGB(surf->format, r, g, b)); }
  void _line(SDL_Surface* surf, int x0, int y0, int x1, int y1, 
	     Uint32 color);
  
  void _try_pixel(bool& res,
		  SDL_Surface* surf,
		  Uint32 color,
		  int x, int y);
    
  //
  Uint32 _color_from_id(SDL_Surface* surf, int id);
  // disp sensor values
  void _disp_bb();
  void _disp_goals();
  void _disp_switches();
  void _disp_Radars();
  void _disp_bumpers();
  void _disp_Lasers();
  void _disp_LightSensors();
  void _disp_camera();
  //
};

#endif	    
