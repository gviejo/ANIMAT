#ifndef NAVIGATION_HH_
#define NAVIGATION_HH_

#include <iostream>
#include "../tools/smart_ptr.h"
#include "Robot.hpp"
#include "Map.hpp"
#include "Posture.hpp"
#include "Display.hpp"
#include "../tools/Vector.hpp"

class Navigation
{
protected:
  SPTR<Map> map;
  SPTR<Posture> position;
  SPTR<Robot> robot;
  SPTR<Display> display;
  float _laser_size;
  int _nb_laser;
  int _taille_entree;
  int _taille_sortie;
  float inter_laser_angle;
  float _speed_factor;
  SPTR<Vector> perception;
  float speed;
  float left_wheel;
  float right_wheel;
  SPTR<Vector> _entree;
  SPTR<Vector> _sortie;

public:
  Navigation();
  Navigation(const char* file, 
	     float start_x, 
	     float start_y,
	     float laser_size, 
	     int nb_laser,
	     float speed_factor,
	     int taille_entree,
	     int taille_sortie);

  void update(int time_step);
  SPTR<Vector> getPerception(){return perception;}
  SPTR<Robot> getRobot(){return robot;}
  SPTR<Posture> getPosture(){return  position;}
  SPTR<Vector> getEntree(){return _entree;}
  SPTR<Vector> getSortie(){return _sortie;}
  void bigUpdate(int nb_update);
  SPTR<Vector> meanLaser(SPTR<Vector> perception_i);

protected:
  void fillPerception();
  void calculateOrientation();
};

#endif
