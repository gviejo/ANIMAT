#ifndef   	ROBOT_HH_
# define   	ROBOT_HH_

#include <vector>
#include "../tools/smart_ptr.h"
#include "Map.hpp"
#include "Posture.hpp"
#include "Laser.hpp"
#include "Radar.hpp"
#include "LightSensor.hpp"
#include "LinearCamera.hpp"

class Robot
{
protected:
  bool _check_collision(SPTR<Map> m);
  void _update_bb();
  float _radius;
  SPTR<Posture> _pos;
  bool _left_bumper, _right_bumper;
  std::vector< SPTR<Laser> > _Lasers;
  std::vector<Radar> _Radars;
  std::vector<LightSensor> _LightSensors;
  LinearCamera _camera;
  bool _use_camera;
  bool _collision;
  unsigned int _color;
 
public:
  struct BoundingBox { float x, y, w, h; };
  enum status_t { free = 0, obstacle = 255};
  BoundingBox _bb;
  
  Robot(float radius) 
  {
    _radius = radius;
    //    _pos(new Posture(0, 0, 0));
    _left_bumper = false;
    _right_bumper = false;
    _use_camera = false;
    _collision = false;
    _color = 1   ;
    _bb.w = _radius * 2 + 8;
    _bb.h = _radius * 2 + 8;      
    _update_bb();
  }
  Robot(float radius, SPTR<Posture> pos) 
  {
    _radius = radius;
    _pos = pos;
    _left_bumper = false;
    _right_bumper = false;
    _use_camera = false;
    _collision = false;
    
    _bb.w = _radius * 2 + 8;
    _bb.h = _radius * 2 + 8;      
    _update_bb();
  }
    //
  void reinit()
  {
    _collision = false;
    _left_bumper = false;
    _right_bumper = false;
  }
  
  void move(float v1, float v2, SPTR<Map> m);
  SPTR<Posture> get_pos() const { return _pos; }
  void set_pos(SPTR<Posture> pos) { _pos = pos; }
  const BoundingBox& get_bb() const { return _bb; }
  float get_radius() const { return _radius; }
  bool get_collision() const { return _collision;}
    //
  bool get_left_bumper() const { return _left_bumper; }
  bool get_right_bumper() const { return _right_bumper; }
  
  // Lasers
  void add_Laser(SPTR<Laser> l) { _Lasers.push_back(l); }
  SPTR<Laser> get_Laser(int i) const { return _Lasers[i]; }
  int get_Lasers_size() const { return _Lasers.size();}
  //void show_Laser_activity(); 

  // Radars
  void add_Radar(const Radar& r){ _Radars.push_back(r); }
  const std::vector<Radar>& get_Radars() const { return _Radars; }

  // light sensors
  void add_LightSensor(const LightSensor& l) { _LightSensors.push_back(l); }
  const std::vector<LightSensor>& get_LightSensors() const { return _LightSensors; }
  void set_color(unsigned int color) {_color=color;}
  unsigned int color() const {return _color;}
  
  // camera
  void use_camera(const LinearCamera& c) { _camera = c; _use_camera = true; }
  void use_camera() { _use_camera = true; }
  const LinearCamera& get_camera() const { return _camera; }
  bool using_camera() const { return _use_camera; }
  
  };



#endif	    /* !ROBOT_HH_ */
