#ifndef NAVIGATION_HH_
#define NAVIGATION_HH_

#include <iostream>
#include "../tools/smart_ptr.h"
#include "Robot.hpp"
#include "Map.hpp"
#include "Posture.hpp"
#include "Display.hpp"
#include "../tools/Vector.hpp"
#include <deque>

class Navigation
{
protected:
  SPTR<Map> map;
  SPTR<Posture> position;
  SPTR<Robot> robot;
  SPTR<Display> display;
  float _laser_size;
  int _nb_laser;
  float inter_laser_angle;
  float _speed_factor;
  float speed;
  float left_wheel;
  float right_wheel;
  SPTR<Vector> perception;
  SPTR<Vector> _output;
  std::deque<float> _input;
  //SPTR<Vector> _input;

public:
  Navigation();
  Navigation(const char* file, 
	     float start_x, 
	     float start_y,
	     float laser_size, 
	     int nb_laser,
	     float speed_factor,
	     int delay);

  void update(int time_step);
  SPTR<Vector> getOutput() {return _output;}
  std::deque<float> getInput() {return _input;}
  //SPTR<Vector> getInput() {return _input;}
  SPTR<Robot> getRobot(){return robot;}
  SPTR<Posture> getPosture(){return  position;}
  
protected:
  void fillPerception();
  void calculateOrientation();
  float computeMean(int side);
  void computeOutput();
};

#endif
