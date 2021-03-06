#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>
#include "../tools/smart_ptr.h"
#include "misc.hpp"
#include "Goal.hpp"
#include "IlluminatedSwitch.hpp"
#include "Posture.hpp"


class Map {
public:
  enum status_t { free = 0, obstacle = 255};
  
  typedef boost::shared_ptr<illuminated_switch> ill_sw_t;


  Map(const char* fname, float real_w, float real_h) 
  {
    _real_w = real_w;
    _real_h = real_h;
    
    _read_file(fname);
    
    if (_w == _h) 
      _fx = _w / _real_w;
  }
  
  status_t get_pixel(unsigned x, unsigned y) const
  {
    return (y * _h + x >= 0 && y * _h + x < _data.size()) ?
        _data[y * _h + x]
      : _data[_data.size()-1];
  }
  void set_pixel(unsigned x, unsigned y, status_t v)
  {
    if (y * _h + x >= 0 && y * _h + x < _data.size())
      _data[y * _h + x] = v;

  }
  status_t get_real(float x, float y) const { return get_pixel(real_to_pixel(x), real_to_pixel(y)); }
  int real_to_pixel(float x) const { return (unsigned) roundf(x * _fx); }
  float pixel_to_real(unsigned i) const { return i / _fx; }
  float get_real_w() const { return _real_w;}
  float get_real_h() const { return _real_h;}
  unsigned get_pixel_w() const { return _w;}
  unsigned get_pixel_h() const { return _h;}
   
  bool check_inter_pixel(int x1, int y1,
			 int x2, int y2,
			 int& x_res, int& y_res) const 
  {
    int i;               // loop counter                                              
    int ystep, xstep;    // the step on y and x axis                                  
    int error;           // the error accumulated during the increment                
    int errorprev;       // *vision the previous value of the error variable          
    int y = y1, x = x1;  // the line points                                           
    int ddy, ddx;        // compulsory variables: the double values of dy and dx      
    int dx = x2 - x1;
    int dy = y2 - y1;
    bool inter = _try_pixel(y1, x1);
    if (dy < 0) { ystep = -1; dy = -dy; } else ystep = 1;
    if (dx < 0) { xstep = -1; dx = -dx; } else xstep = 1;
    ddy = dy * 2;
    ddx = dx * 2;
    if (ddx >= ddy) // first octant (0 <= slope <= 1)                                 
      {
        errorprev = error = dx;
        for (i = 0 ; i < dx ; i++)
          {  // do not use the first point (already done)                             
            x += xstep;
            error += ddy;
            if (error > ddx)
	      {
                y += ystep;
                error -= ddx;
                if (error + errorprev < ddx)  // bottom square also                   
                  inter = inter || _try_pixel(y - ystep, x);
                else if (error + errorprev > ddx)  // left square also                
                  inter = inter || _try_pixel(y, x - xstep);
                else // corner: bottom and left squares also                          
                  {
                    inter = inter || _try_pixel(y - ystep, x);
                    inter = inter || _try_pixel(y, x - xstep);
                  }
              }
            inter = inter || _try_pixel(y, x);
            errorprev = error;
            if (inter)
              {
                x_res = x;
                y_res = y;
                return true;
              }
          }
      }
    else
      {  // the same as above                                                         
        errorprev = error = dy;
        for (i = 0 ; i < dy ; i++)
          {
            y += ystep;
            error += ddx;
            if (error > ddy){
              x += xstep;
              error -= ddy;
              if (error + errorprev < ddy)
                inter = inter || _try_pixel(y, x - xstep);
              else if (error + errorprev > ddy)
                inter = inter || _try_pixel(y - ystep, x);
              else
                {
                  inter = inter || _try_pixel(y, x - xstep);
                  inter = inter || _try_pixel(y -  ystep, x);
                }
            }
            inter = inter || _try_pixel(y, x);
            errorprev = error;
            if (inter)
              {
                x_res = x;
                y_res = y;
                return true;
              }
          }
      }
    return false;
  }
  

  bool check_inter_real(float x1, float y1,
			float x2, float y2,
			float& x_res, float &y_res) const
  {
    int px = 0, py = 0;
    bool res = check_inter_pixel(real_to_pixel(x1), real_to_pixel(y1),
				 real_to_pixel(x2), real_to_pixel(y2),
				 px, py);
    x_res = pixel_to_real(px);
    y_res = pixel_to_real(py);
    return res;
  }

  int check_inter_is(float x1, float y1,
		     float x2, float y2) const 
  {
    // list intersections with rays                                                   
    std::vector<ill_sw_t> res;
    for (size_t i = 0; i < _illuminated_switches.size(); ++i)
      {
        ill_sw_t isv = _illuminated_switches[i];
        float xtmp, ytmp;
        if (isv->get_on()
            && _check_inter_ray_circle(x1, y1, x2, y2,
				       isv->get_x(), isv->get_y(),
				       isv->get_radius())
            && !check_inter_real(x1, y1, isv->get_x(), isv->get_y(), xtmp, ytmp))
          res.push_back(isv);
      }
    if (res.empty())
      return -1;
    // return the closest                                                             
    std::sort(res.begin(), res.end(), ClosestSwitch_f(x1, y1));
    return res[0]->get_color();
  }

  const std::vector<goal> get_goals() const { return _goals; }

  void add_goal(goal g) { _goals.push_back(g); }
  

  void add_illuminated_switch(ill_sw_t is)
  { _illuminated_switches.push_back(is); }

  const std::vector<ill_sw_t>& get_illuminated_switches() const
  { return _illuminated_switches; }

  ill_sw_t get_illuminated_switch_by_color(int color)
  {
    for (size_t i = 0; i < _illuminated_switches.size(); ++i)
      if (_illuminated_switches[i]->get_color() == color)
	return _illuminated_switches[i];
    assert(0);
    return ill_sw_t();
  }

  void clear_illuminated_switches()
  { _illuminated_switches.clear(); }

  void update(SPTR<Posture> robot_pos)
  {
    for (size_t i = 0; i < _illuminated_switches.size(); ++i)
      _illuminated_switches[i]->try_to_activate(robot_pos);
      }
  void terrain_switch(const std::string &fname)
  {
    _read_file(fname);
  }

  // Draws a rectangle with (x,y) the upper left point and (lx,ly) the size         
  void draw_rect(int x, int y, int lx, int ly)
  {
    for (int i=0;i<lx;i++)
      for (int j=0;j<ly;j++) {
        if ((x+i) >= 0 && (y+j) >= 0
            && (x+i) < get_pixel_w()
            && (y+j) < get_pixel_h())
          set_pixel(x+i,y+j,obstacle);
      }
      }
protected:
  
  std::vector<status_t> _data;
  std::vector<goal> _goals;
  std::vector<ill_sw_t> _illuminated_switches;
  //                                                                                                                        
  int _w, _h;
  float _real_w, _real_h;
  float _fx;

  void _read_file(const std::string& fname)
  {
    std::string str; 
    std::ifstream ifs(fname.c_str());

    ifs >> str >> _w >> _h;
    _data.resize(_w * _h);
    int k = _w * _h / 8;
    char buffer[k];
    
    ifs.read((char*)buffer, k);

    for (int i = 0; i < k-1;++i) {
      for (int j = 0; j <8 ;++j) {
	_data[i*8+j] = _get_bit(buffer[i+1], j) ? obstacle : free; 	
      }
    }
  }

                
  bool _get_bit(char c, int i) const { return (c & (1 << (7 - i))); }

  
  bool _try_pixel(int x, int y) const {
    if (x >= 0 && y >= 0
        && x < get_pixel_w()
        && y < get_pixel_h()
        && get_pixel(y, x) == free)
      return false;
    else
      return true;
  }
                                                                                                                       
  bool _check_inter_ray_circle(float x1, float y1,
			       float x2, float y2,
			       float xr, float yr, float radius) const {
    // check if the object is on the right side of the camera                                                                 
    float dot = (x2 - x1) * (xr - x1) + (y2 - y1) * (yr - y1);
    if (dot < 0)
      return false;
    float area2 = fabs((x2 - x1) * (yr - y1) -  (y2 - y1) * (xr - x1));
    float dx = x2 - x1;
    float dy = y2 - y1;
    float lab = sqrt(dx * dx + dy * dy);
    float h = area2 / lab;
    if (h < radius)
      return true;
    return false;
  }
                                                                        
};

#endif
