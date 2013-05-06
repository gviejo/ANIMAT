#ifndef EXPERT_HH_
#define EXPERT_HH_

#include <iostream>
#include "../tools/Vector.hpp"
#include "../tools/smart_ptr.h"
#include "Loss.hpp"
#include "SigModule.hpp"
#include "Module.hpp"
#include "TanModule.hpp"
#include "RecurrentModule.hpp"

class Expert {
protected:
  std::vector< SPTR<Module> > vect;
  SPTR<Loss> loss;
  int _nb_module;
  int _input_size;
  int _output_size;
  int _nb_h_neurons;

public: 
  Expert(int dimOutput);
  Expert(gsl_rng* rgen, int nb_module, int input_size, int output_size, int nb_h_neuron);
  void addModules(SPTR<Module> m);
  SPTR<Vector> getSortie(SPTR<Vector> entree);
  SPTR<Module> getModule(int i);
  SPTR<Vector> forward(SPTR<Vector> input, SPTR<Vector> output);
  SPTR<Loss> getLoss();

  void gradientStep(double epsilon_gradient, SPTR<Vector> input, SPTR<Vector> output, float proba_gate, float epsilon);
  void backward(SPTR<Vector> input, SPTR<Vector> output, float proba_gate);
  double computeError(SPTR<Vector> input, SPTR<Vector> output);

 
 };

#endif
