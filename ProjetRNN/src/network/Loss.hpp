#ifndef LOSS_HH_
#define LOSS_HH_

#include <iostream>
#include "../tools/Vector.hpp"

class Loss
{
protected:
  int _nb_h_neurons;
  int _nb_output;
  SPTR<Vector> delta;
  double value;

public:
  Loss();
  Loss(int nb_h_neurons, int nb_output);
  SPTR<Vector> getDelta();
  double getValue();
  void backward(SPTR<Vector> input, SPTR<Vector> output, float proba_gate);
  void computeValue(SPTR<Vector> input, SPTR<Vector> output);
};
#endif
