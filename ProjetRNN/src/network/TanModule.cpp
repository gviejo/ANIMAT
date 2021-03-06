#include "TanModule.hpp"
#include <iostream>

//#include "../tools/smart_ptr.h"
//#include "../tools/Vector.hpp"
//#include "../tools/Matrix.hpp"

TanModule::TanModule() {
  Module();
}

TanModule::TanModule(int taille_entree,int taille_sortie){

  _taille_entree = taille_entree; _taille_sortie = taille_sortie;
  Module(taille_sortie, taille_sortie);
  sortie.reset(new Vector(_taille_sortie));
  delta.reset(new Vector(_taille_sortie));
}

TanModule::~TanModule(){
}


SPTR<Vector> TanModule::getSortie(){
  //sortie->display();
  return(sortie);
}


float TanModule::tan(float x)
{
  return (exp(2*x)-1)/(exp(2*x)+1);
}

void TanModule::initGradient() {}

void TanModule::updatePoids(double pasGradient) {}

void TanModule::forward(SPTR<Vector> entree)
{
  for(int i=0;i<_taille_entree;i++)
    {
      float tmp = tan(entree->getValue(i));
      sortie->setValue(i,tmp);
  }
}


void TanModule::backward_computeDeltaInputs(SPTR<Vector> input, SPTR<Vector> deltaOutput){
  for(int i=0; i<_taille_entree;i++){
    float tmp = (4*exp(2*input->getValue(i)))/pow((exp(2*input->getValue(i))+1),2);
    delta->setValue(i, deltaOutput->getValue(i)*tmp);    
  }
}

void TanModule::backward_computeDerivative(SPTR<Vector> input){
  for(int i=0; i<_taille_entree;i++){
    float tmp = (4*exp(2*input->getValue(i)))/pow((exp(2*input->getValue(i))+1),2);
    delta->setValue(i, tmp);    
  }
}



