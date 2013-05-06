#include <iostream>
#include "Laser.hpp"

void Laser :: update(SPTR<Posture> pos,
		      SPTR<Map> m)
{
    float x2 = cosf(_angle + pos->theta()) * _range + pos->x() + _gap_dist * cosf(_gap_angle + pos->theta());
    float y2 = sinf(_angle + pos->theta()) * _range + pos->y() + _gap_dist * sinf(_gap_angle + pos->theta());
    

    // convert to pixel
    int xx1 = m->real_to_pixel(pos->x() + _gap_dist * cosf(_gap_angle + pos->theta()));
    int yy1 = m->real_to_pixel(pos->y() + _gap_dist * sinf(_gap_angle + pos->theta()));
    int xx2 = m->real_to_pixel(x2);
    int yy2 = m->real_to_pixel(y2);
    // check intersection

    _x_pixel = m->real_to_pixel(x2), _y_pixel = m->real_to_pixel(y2);

    bool inter = m->check_inter_pixel(xx1, yy1, xx2, yy2, _x_pixel, _y_pixel);
     _x_pixel = std::min(std::max(0, _x_pixel), (int)m->get_pixel_w());
     _y_pixel = std::min(std::max(0, _y_pixel), (int)m->get_pixel_h());
    //assert(_x_pixel >= 0);
    //assert(_y_pixel >= 0);

    // convert back to real
    _x = m->pixel_to_real(_x_pixel);
    _y = m->pixel_to_real(_y_pixel);
 
	float px = pos->x() + _gap_dist * cosf(_gap_angle + pos->theta()) - _x;
	float py = pos->y() + _gap_dist * sinf(_gap_angle + pos->theta()) - _y;    
	_dist = sqrtf(px * px  + py * py);
    
}
  

