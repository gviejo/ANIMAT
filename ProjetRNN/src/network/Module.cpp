#include <iostream>
#include "Module.hpp"
//#include "../tools/smart_ptr.h"
//#include "../tools/Vector.hpp"
//#include "../tools/Matrix.hpp"

Module::Module() {}

Module::~Module() {}

void Module::forward(SPTR<Vector> entree){
  	double tmp = 0.0;
	for(int i=0;i<_taille_sortie;i++){
		tmp=0.0;
		for(int j=0;j<_taille_entree;j++){
			tmp=tmp+entree->getValue(j)*poids->getValue(j,i);
		}
		sortie->setValue(i, tmp);		
	}
  }

SPTR<Vector> Module::getSortie(){
    return(sortie);
}

void Module::randomize(gsl_rng* rgen) 
{
  for (int i = 0; i < _taille_entree; i++) {
    for (int j = 0; j<_taille_sortie; j++) {
      double tmp = gsl_ran_flat(rgen, 0, 1);
      //double tmp = gsl_ran_gaussian(rgen, 1);
      float t = float(tmp);
      poids->setValue(i, j, t);
    }
  }
}

void Module::updatePoids(double pasGradient){
  for(int i =0;i<_taille_entree;i++){
    for(int j=0;j<_taille_sortie;j++){
      poids->setValue(i,j,poids->getValue(i,j)+pasGradient * gradient->getValue(i,j));
    }
  }
}

void Module::initGradient(){
  for(int i =0;i<_taille_entree;i++){
    for(int j=0;j<_taille_sortie;j++){
      gradient->setValue(i,j, 0.0);
    }
  }
}


void Module::backward_updateGradient(SPTR<Vector> input, SPTR<Vector> deltaOutput){
  for (int i=0; i<_taille_entree;i++) {
    for (int j=0; j<_taille_sortie;j++) {
      gradient->setValue(i, j, deltaOutput->getValue(j)*input->getValue(i));
    }
  }
}


void Module::backward_computeDeltaInputs(SPTR<Vector> input, SPTR<Vector> deltaOutput){

  for(int i=0; i<_taille_entree;i++){
    double tmp=0.0;
    for(int j=0; j<_taille_sortie;j++){
      tmp=tmp+deltaOutput->getValue(j)*poids->getValue(i,j);
    }
    delta->setValue(i,tmp);
  }
}

SPTR<Vector> Module::getState(){}

void Module::updateState(SPTR<Vector> new_state){}
