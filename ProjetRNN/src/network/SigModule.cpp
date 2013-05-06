#include "SigModule.hpp"
#include <iostream>

//#include "../tools/smart_ptr.h"
//#include "../tools/Vector.hpp"
//#include "../tools/Matrix.hpp"

SigModule::SigModule() {
  Module();
}

SigModule::SigModule(int taille_entree,int taille_sortie){

  _taille_entree = taille_entree; _taille_sortie = taille_sortie;
  Module(taille_sortie, taille_sortie);
  sortie.reset(new Vector(_taille_sortie));
  delta.reset(new Vector(_taille_sortie));
}

SigModule::~SigModule(){
}


SPTR<Vector> SigModule::getSortie(){
    return(sortie);
}


float SigModule::sigmoid(float x)
{
  return 1/(1+exp(-x));
}

void SigModule::initGradient() {}

void SigModule::updatePoids(double pasGradient) {}

void SigModule::forward(SPTR<Vector> entree)
{
  for(int i=0;i<_taille_entree;i++)
    {
      float tmp = sigmoid(entree->getValue(i));
      sortie->setValue(i,tmp);
  }
}


void SigModule::backward_computeDeltaInputs(SPTR<Vector> input, SPTR<Vector> deltaOutput){
  for(int i=0; i<_taille_entree;i++){
    float tmp = exp(-input->getValue(i))/std::pow((1+exp(-input->getValue(i))),2);
    delta->setValue(i, deltaOutput->getValue(i)*tmp);    
  }
}

void SigModule::backward_computeDerivative(SPTR<Vector> input) {
  for (int i=0;i<_taille_entree;i++) {
    float tmp = exp(-input->getValue(i))/std::pow((1+exp(-input->getValue(i))),2);
    delta->setValue(i, tmp);
  }
}


