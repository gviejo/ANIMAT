#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <gsl/gsl_randist.h>
#include "tools/smart_ptr.h"
#include "tools/Vector.hpp"
#include "tools/Matrix.hpp"
#include "network/Layer.hpp"
#include "network/Expert.hpp"
#include "simulation/Navigation.hpp"


using namespace std;

int main(int argc, char* argv[]) {
  gsl_rng* rgen;
  rgen=gsl_rng_alloc(gsl_rng_rand48);
  gsl_rng_set(rgen,time(0));
  ///////////////////////////////
  //Network Parameters
  int nb_expert = 5;
  int nb_module = 2;
  int input_size = 3*6;
  int output_size = 6;
  int nb_hidden_neuron = 5;
  float sigma = 1;
  float epsilon_gate = 0.1;
  float eta = 0.0001;
  float epsilon_app = 0.0001;
  ///////////////////////////////
  //Navigation Parameters
  int x_start = 150;
  int y_start = 53;
  int laser_size = 100;
  int nb_laser = 16;
  float speed_factor = 0.1;
  //int taille_entree=input_size;
  //////////////////////////////
  //Time parameters
  int delay = 1;
  std::queue< SPTR<Vector> > array_perception;
  /////////////////////////////
  std::ofstream fichier;

  SPTR<Navigation> navigator(new Navigation("maze.pbm", 
					    x_start, 
					    y_start, 
					    laser_size, 
					    nb_laser, 
					    speed_factor,
					    input_size,
					    output_size));
  
  SPTR<Layer> layer(new Layer(rgen, nb_expert,nb_module, 
			                    input_size, 
			                    output_size, 
			                    nb_hidden_neuron,
			                    sigma,
			                    epsilon_gate,
			                    eta));


  std::cout << "ite" << "  " << "gate" << std::endl;
  for (int it=0;it<7000;it++) 
    {
      //Avancement du robot
      navigator->bigUpdate(it);
      //Apprentissage des Experts
      layer->backwardLayer(it, epsilon_app, navigator->getEntree(), navigator->getSortie());
      //Affichage du meilleur expert a chaque iteration
      std::cout << " " << it;
      std::cout << "   " << layer->getBest();
      std::cout << "\n";     
    }

  return 0;

};

