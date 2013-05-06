#ifndef FASTSIM_RADAR_HPP_
#define FASTSIM_RADAR_HPP_

#include <boost/shared_ptr.hpp>
#include "Posture.hpp"
#include "Map.hpp"
#include "../tools/smart_ptr.h"
#include "misc.hpp"

  /// a Radar detects a given goal in one of the n slices
  /// Radar SEE TROUGH OBSTACLES
class Radar
{
protected:
  // the "color" (i.e. goal identifier) detected by this "Radar"
  int _color;
  // the number of pie-slices
  int _nb_slices;
  // the size of a slice
  float _inc;
  // the activated slices (-1 if the goal is not visible)
  int _activated_slice;
  // true if the Radar can see trough walls
  // get_activated_slices() will return -1 if the goal is not visible
  bool _through_walls;

public:
  Radar(int color, int nb_slices, bool through_walls = true) 
  {
    _color = color;
    _nb_slices = nb_slices;
    _inc = (2 * M_PI / nb_slices);
    _activated_slice = 0;
    _through_walls = through_walls;
  }
  int update(SPTR<Posture> pos,
	     SPTR<Map> map);
  int get_activated_slice() const { return _activated_slice; }
  int get_nb_slices() const { return _nb_slices; }
  int get_color() const { return _color; }
  float get_inc() const { return _inc; }
  };

#endif
