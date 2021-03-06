#include <iostream>
#include "../tools/smart_ptr.h"
#include "../tools/Vector.hpp"
#include "Loss.hpp"

Loss:: Loss(){}
Loss:: Loss(int size){
  _size=size;
  value=0.0;
  delta.reset(new Vector(_size));
}

SPTR<Vector> Loss:: getDelta(){
  return(delta);
}

double Loss::getValue(){
  return(value);
}

void Loss::backward(SPTR<Vector> input, SPTR<Vector> output, float proba_gate){
  for(int i=0; i<input->size();i++){
    delta->setValue(i, proba_gate*(input->getValue(i)-output->getValue(i)));
  }
  
}

void Loss::computeValue(SPTR<Vector> input, SPTR<Vector> output){
   
  value =0.0;
  for(int i=0; i<input->size();i++){
    value=value + ((input->getValue(i)-output->getValue(i))*(input->getValue(i)-output->getValue(i)));
  }

}


