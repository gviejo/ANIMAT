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
		       int taille_entree,
			int taille_sortie)
		       
{
  map.reset(new Map(file, 600, 600));
  position.reset(new Posture(start_x, start_y, 0));
  robot.reset(new Robot(15.0, position));
  display.reset(new Display(map, robot));
  _laser_size = laser_size; _nb_laser = nb_laser; _speed_factor = speed_factor;
  inter_laser_angle = 2*M_PI/_nb_laser;
  perception.reset(new Vector(nb_laser));
  _taille_entree=taille_entree;
  _taille_sortie=taille_sortie;
  _entree.reset(new Vector(_taille_entree));
  _sortie.reset(new Vector(_taille_sortie));
  
  
  for (int i = -4;i<12;i++){
    SPTR<Laser> laser(new Laser(inter_laser_angle*i, _laser_size));
    robot->add_Laser(laser);
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


void Navigation::update(int time_step)
{
  map->update(robot->get_pos());
  display->update();
  fillPerception();
  calculateOrientation();
  if(std::abs(right_wheel-left_wheel)>=0.4){
     robot->move((_speed_factor*speed+right_wheel)-0.5, (_speed_factor*speed+left_wheel)-0.5, map);
  }
  else robot->move(0.5,0.5,map);
}

void Navigation::bigUpdate(int nb_update){
	SPTR<Vector> tmp;
	tmp.reset(new Vector(_taille_sortie));
	int i=0;
	for(int k=nb_update;k<nb_update+3;k++){
		int j=0;
		update(k);
		tmp=meanLaser(getPerception());
		do{
			_entree->setValue(i,tmp->getValue(j));
			i++;
			j++;
		}while(j<_taille_sortie);
	}
	update(nb_update+3);
	_sortie=meanLaser(getPerception());
}

SPTR<Vector> Navigation::meanLaser(SPTR<Vector> perception_i){
	SPTR<Vector> mean;

	mean.reset(new Vector(_taille_sortie));

	mean->setValue(0,(perception_i->getValue(15)+perception_i->getValue(0)+perception_i->getValue(1))/3);
	mean->setValue(1,(perception_i->getValue(2)+perception_i->getValue(3)+perception_i->getValue(4)+perception_i->getValue(5))/4);
	mean->setValue(2,(perception_i->getValue(6)+perception_i->getValue(7)+perception_i->getValue(8)+perception_i->getValue(9)+perception_i->getValue(10))/5);
	mean->setValue(3,(perception_i->getValue(11)+perception_i->getValue(12)+perception_i->getValue(13)+perception_i->getValue(14))/4);
	mean->setValue(4,right_wheel);
	mean->setValue(5,left_wheel);

	return(mean);
}



