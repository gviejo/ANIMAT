#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <gsl/gsl_randist.h>
#include "tools/smart_ptr.h"
#include "tools/Vector.hpp"
#include "tools/Matrix.hpp"
#include "network/Layer.hpp"
#include "network/Expert.hpp"
#include "simulation/Navigation.hpp"
#include <boost/thread/thread.hpp>

int main(int argc, char* argv[]) {
  std::cout.precision(3);
  gsl_rng* rgen; 
  rgen=gsl_rng_alloc(gsl_rng_rand48);
  gsl_rng_set(rgen,time(0));
  ///////////////////////////////
  //Network Parameters
  int nb_expert = 5;
  int nb_module = 2;
  int input_size = 6;
  int output_size = input_size;
  int nb_hidden_neuron = 4; 
  float sigma = 0.8;
  float epsilon_gate = 1;
  float eta = 0.1;
  float epsilon_app = 0.1;
  ///////////////////////////////
  //Navigation Parameters
  int x_start = 150;
  int y_start = 53;
  int laser_size = 100;
  int nb_laser = 16;
  float speed_factor = 0.5;
  //////////////////////////////
  //Time parameters
  int delay = 1;
  /////////////////////////////
  
  SPTR<Navigation> navigator(new Navigation("maze.pbm",
					    x_start, 
					    y_start, 
					    laser_size, 
					    nb_laser, 
					    speed_factor,
					    delay));
  
  SPTR<Layer> layer(new Layer(rgen, nb_expert,nb_module, 
			      input_size, 
			      output_size, 
			      nb_hidden_neuron,
			      sigma,
			      epsilon_gate,
			      eta));
  
  
  for (int it=0;it<200000;it++) 
    {      
      //Avancement du robot
      navigator->update(it);            

      //Apprentissage des Experts
      layer->backwardLayer(it, epsilon_app, navigator->getInput(), navigator->getOutput());
      
      //layer->display_all();
      //layer->display_error();
      layer->display_winner(it);
    }
  
  return 0;
};


