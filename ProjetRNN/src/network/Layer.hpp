#ifndef LAYER_HH_
#define LAYER_HH_

#include <iostream>
#include "../tools/smart_ptr.h"
#include <vector>
#include <queue>
#include <math.h>
#include "../tools/Vector.hpp"
#include "../tools/Matrix.hpp"
#include "../tools/Plot.hpp"
#include "Expert.hpp"
#include <gsl/gsl_randist.h>


class Layer
{
protected:
  std::vector< SPTR<Expert> > _layer;
  std::vector< SPTR<Vector> > _output;
  int _nb_expert;
  int _nb_module;
  int _input_size;
  int _output_size;
  int _nb_hidden_layers;
  int _nb_hidden_neuron;
  float _sigma,_epsilon,_eta;
  SPTR<Vector> _error_layer;
  SPTR<Vector> _gate;
  SPTR<Vector> _proba_gate;
  SPTR<Vector> _exp_state;
  SPTR<Vector> _grad;
  SPTR<Vector> _state;
  std::queue< SPTR<Vector> > array_state;
  SPTR<Vector> _input;
  SPTR<Plot> _plot;
  int best;

public:
  Layer();
  Layer(gsl_rng* rgen, int nb_expert, int nb_module, int input_size, int output_size, int nb_hidden_neuron, float sigma, float epsilon, float eta) 
  {
    _nb_expert = nb_expert;
    _nb_module = nb_module;
    _input_size = input_size;
    _output_size = output_size;
    _nb_hidden_neuron = nb_hidden_neuron;
    _sigma = sigma;
    _epsilon = epsilon;
    _eta = eta;
    _output.resize(_nb_expert);
    _gate.reset(new Vector(_nb_expert));
    _exp_state.reset(new Vector(_nb_expert));
    _proba_gate.reset(new Vector(_nb_expert));
    _grad.reset(new Vector(_nb_expert));
    _state.reset(new Vector(_nb_expert));
    _input.reset(new Vector(_input_size));
    _error_layer.reset(new Vector(_nb_expert));
    _state->initialisationZero();
    array_state.push(_state);
    array_state.push(_state);
    _plot.reset(new Plot(_nb_expert));
    for (int i=0;i<_nb_expert;i++)
      {
	SPTR<Expert> expert(new Expert(rgen, _nb_module, _input_size, _output_size, _nb_hidden_neuron));
	_layer.push_back(expert);
      }
  } 
  
  SPTR<Expert> getExpert(int i);

  void forward(SPTR<Vector> input, SPTR<Vector> output);
  void backwardLayer(int it, float epsilon, std::deque<float> input, SPTR<Vector> output);
  void backwardLayer(int it, float epsilon, SPTR<Vector> input, SPTR<Vector> output);
  void computeErrorLayer(SPTR<Vector> input, SPTR<Vector> output);  
  void computeGate();
  void computePropaGate();
  void computeGradientState();
  void updateState();
  SPTR<Vector> getOutput(int i);
  void display_all();
  void display_error();
  void display_winner(int it);
};

#endif
