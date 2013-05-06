#ifndef   	LASER_HH_
# define   	LASER_HH_
#include "Map.hpp"
#include "Posture.hpp"
#include <boost/shared_ptr.hpp>
#include "../tools/smart_ptr.h"

class Laser
{
public:
  Laser(float angle, float range, float gap_dist = 0.0f, float gap_angle = 0.0f)
  {
    _angle = angle;
    _range = range;
    _gap_dist = gap_dist;
    _gap_angle = gap_angle;
    _x = 0;
    _y = 0;
    _x_pixel = 0;
    _y_pixel = 0;
    _dist = gap_dist;
  }
  void update(SPTR<Posture> pos, SPTR<Map> m);	       
  float get_dist() const { return _dist; }
  float get_angle() const { return _angle; }
  float get_range() const { return _range; }
  float get_gap_dist() const { return _gap_dist; }
  float get_gap_angle() const { return _gap_angle; }
  // intersection point in world coordinates
  float get_x() const { return _x; }
  float get_y() const { return _y; }
  // intersection point in pixel coordinates
  int get_x_pixel() const { return _x_pixel; }
  int get_y_pixel() const { return _y_pixel; }
  protected:
  float _angle;
  float _range;
  float _gap_dist, _gap_angle;//polar coordinates of the Laser (reference = robot)
  float _x, _y;
  int _x_pixel, _y_pixel;
  float _dist;
  // 
  bool _try_pixel(SPTR<Map> m, int x, int y);
  bool _line_inter(SPTR<Map> m,
		   int y1, int x1, // src
		     int y2, int x2, // dest
		     int& x_res, int& y_res //res
		     );

};



#endif	    /* !LASER_HH_ */
