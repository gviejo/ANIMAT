#include <iostream>
#include "Map.hpp"
#include "Posture.hpp"
#include "Laser.hpp"
#include "Navigation.hpp"

Navigation::Navigation(const char* file, 
		       float start_x, 
		       float start_y, 
		       float laser_size,
		       int nb_laser,
		       float speed_factor, 
		       int delay)
		       
{
  map.reset(new Map(file, 600, 600));
  position.reset(new Posture(start_x, start_y, 0));
  robot.reset(new Robot(15.0, position));
  display.reset(new Display(map, robot));
  _laser_size = laser_size; _nb_laser = nb_laser; _speed_factor = speed_factor;
  inter_laser_angle = 2*M_PI/_nb_laser;
  perception.reset(new Vector(_nb_laser));
  _output.reset(new Vector((_nb_laser/4)+2));
  //_output.reset(new Vector(_nb_laser+2));
  _output->initialisationZero();
  _input.resize(((_nb_laser/4)+2)*delay, 0.0);
  //_input.resize(_nb_laser+2, 0.0);
  
  //Initialisation des lasers
  for (int i = -4;i<12;i++){
    SPTR<Laser> laser(new Laser(inter_laser_angle*i, _laser_size));
    robot->add_Laser(laser);
    }
}

float  Navigation::computeMean(int side)
{
  float tmp = 0.0;
  //very bad 1:front/2:right/3:back/4:left
  switch(side) {
  case 0:
    for (int i = 2;i<7;i++) {
      tmp = tmp+robot->get_Laser(i)->get_dist()/_laser_size;
    }
    return tmp/5;
  case 1:
    for (int i = 7;i<11;i++) {
      tmp = tmp+robot->get_Laser(i)->get_dist()/_laser_size;
    }
    return tmp/4;
  case 2:
    for (int i = 11;i<14;i++) {
      tmp = tmp+robot->get_Laser(i)->get_dist()/_laser_size;
    }
    return tmp/3;
  case 3:
    for (int i = 14;i<16;i++) {
      tmp = tmp+robot->get_Laser(i)->get_dist()/_laser_size;
    }
    for (int i = 0;i<2;i++) {
      tmp = tmp+robot->get_Laser(i)->get_dist()/_laser_size;
    }
    return tmp/4;
  }
}


void Navigation::fillPerception()
{
  for (int i=0;i<_nb_laser;i++)
    {
      perception->setValue(i, robot->get_Laser(i)->get_dist()/_laser_size);
    }
}

void Navigation::calculateOrientation()
{
  SPTR<Vector> xorientation(new Vector((_nb_laser/2)+1));
  SPTR<Vector> yorientation(new Vector((_nb_laser/2)+1));

  for (int i=0;i<(_nb_laser/2)+1;i++){
    xorientation->setValue(i, sin(robot->get_Laser(i)->get_angle())*perception->getValue(i));
    yorientation->setValue(i, cos(robot->get_Laser(i)->get_angle())*perception->getValue(i));
  }

  speed = yorientation->sum();
  if ((xorientation->sum())>0)
    left_wheel = xorientation->sum();
  else
    right_wheel = -1.0*xorientation->sum();
}

void Navigation::computeOutput() {
  for (int i=0;i<_nb_laser/4;i++)
    {
      _input.pop_front();      
      _input.push_back(_output->getValue(i));
      _output->setValue(i, computeMean(i));
    }
  
  _input.pop_front();      
  _input.push_back(_output->getValue(4));
  _output->setValue(4, right_wheel); 
  _input.pop_front();      
  _input.push_back(_output->getValue(5));
  _output->setValue(5, left_wheel); 
  }

/*
void Navigation::computeOutput() 
{
  for (int i = 0;i<_nb_laser;i++) {
    _input.pop_front();
    _input.push_back(_output->getValue(i));
    _output->setValue(i, perception->getValue(i));
  }
  _input.pop_front();
  _input.push_back(_output->getValue(16));
  _output->setValue(16, right_wheel);
  _input.pop_front();
  _input.push_back(_output->getValue(17));
  _output->setValue(17, left_wheel);      
}
*/

void Navigation::update(int time_step)
{
  map->update(robot->get_pos());
  display->update();
  fillPerception();
  calculateOrientation();
  computeOutput();
  
  if(std::abs(right_wheel-left_wheel)>=0.5){
    robot->move((_speed_factor*speed+right_wheel)-0.5, (_speed_factor*speed+left_wheel)-0.5, map);
  }
  else robot->move(0.8, 0.8, map);

  
}



