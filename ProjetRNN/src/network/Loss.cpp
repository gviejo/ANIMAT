#include <iostream>
#include "../tools/smart_ptr.h"
#include "../tools/Vector.hpp"
#include "Loss.hpp"

Loss:: Loss(){}
Loss:: Loss(int nb_h_neurons, int nb_output){
  _nb_h_neurons = nb_h_neurons; _nb_output = nb_output;
  value=0.0;
  delta.reset(new Vector(_nb_h_neurons+_nb_output));
  delta->initialisationZero();
}

SPTR<Vector> Loss:: getDelta(){
  return(delta);
}

double Loss::getValue(){
  return(value);
}

void Loss::backward(SPTR<Vector> input, SPTR<Vector> output, float proba_gate){
  for(int i=_nb_h_neurons; i<_nb_h_neurons+_nb_output;i++){
    //delta->setValue(i, proba_gate*(output->getValue(i)-input->getValue(i)));
    delta->setValue(i, proba_gate*(input->getValue(i)-output->getValue(i)));

  }  
}

void Loss::computeValue(SPTR<Vector> input, SPTR<Vector> output){
  value =0.0;
  float tmp = 0;
  for (int i = 0;i<output->size();i++) 
    {
      tmp = output->getValue(i)-input->getValue(i+_nb_h_neurons);
      value = value+tmp*tmp;
    }
}


