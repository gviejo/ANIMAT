#ifndef FASTSIM_LIGHTSENSOR_HPP_
#define FASTSIM_LIGHTSENSOR_HPP_

#include <boost/shared_ptr.hpp>
#include "Posture.hpp"
#include "Map.hpp"
#include "../tools/smart_ptr.h"

/// detect an colored illuminated switch in the given direction
/// (angle) and within the angular range. There is no range limit.
/// light sensors DONT'T SEE TROUGH OBSTACLES
class LightSensor
{
public:
  LightSensor(int color, float angle, float range) 
  {
    _color = color;
    _angle = angle;
    _range = range;
    _activated = false;
    _num = 0;
  }
  int update(SPTR<Posture> pos,
	     SPTR<Map> Map);
  int	get_color() const { return _color; }
  float get_angle() const { return _angle; }
  float get_range() const { return _range; }
  bool get_activated() const { return _activated; }
  unsigned int get_num() const {return _num;}
  protected:
    // the "color" (i.e. light identifier) detected
  int _color;
  //
  float _angle;
  //
  float _range;
  //
  bool _activated;
  // sensor number (for display only)
  unsigned int _num;
};
#endif
