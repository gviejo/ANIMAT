#include "RecurrentModule.hpp"
#include <iostream>


RecurrentModule::RecurrentModule() {
  Module();
}

RecurrentModule::RecurrentModule(int taille_entree,int taille_sortie, int nb_h_neurons){

  _taille_entree = taille_entree+1; _taille_sortie = taille_sortie; _nb_h_neurons = nb_h_neurons;
  //Module(_taille_entree+_nb_h_neurons+_taille_sortie, _nb_h_neurons+_taille_sortie);
  poids.reset(new Matrix(_taille_entree+_nb_h_neurons+_taille_sortie, _nb_h_neurons+_taille_sortie));

  gradient.reset(new Matrix(_taille_entree+_nb_h_neurons+_taille_sortie, _nb_h_neurons+_taille_sortie));
  
  state.reset(new Vector(_nb_h_neurons+_taille_sortie));
  sortie.reset(new Vector(_taille_sortie));
  buffer.reset(new Vector(_taille_entree+_nb_h_neurons+_taille_sortie));

  dynamic_gradient.reset(new Matrix3D(_taille_entree+_nb_h_neurons+_taille_sortie, _nb_h_neurons+_taille_sortie, _nb_h_neurons+_taille_sortie));
  array_dynamic_gradient.push_back(dynamic_gradient);

}

RecurrentModule::~RecurrentModule(){}

void RecurrentModule::randomize(gsl_rng* rgen)
{
  for (int i = 0; i<_taille_entree+_nb_h_neurons+_taille_sortie;i++) {
    for (int j = 0;j<_nb_h_neurons+_taille_sortie;j++) {
      double tmp = gsl_ran_flat(rgen, 0, 1);
      float t = float(tmp);
      poids->setValue(i, j, t);
    }
  }
}

void RecurrentModule::forward(SPTR<Vector> entree)
{
  buffer->setValue(0, 1); //biais
  for (int i = 1;i<_taille_entree;i++) {
    buffer->setValue(i, entree->getValue(i));}
  
  for (int i = 0;i<_nb_h_neurons+_taille_sortie;i++) {
    buffer->setValue(i+_taille_entree, state->getValue(i));
  }
  double tmp = 0.0;
  for (int i=0;i<_nb_h_neurons+_taille_sortie;i++) {
    tmp = 0.0;
    for (int j=0;j<_taille_entree+_nb_h_neurons+_taille_sortie;j++) {
      tmp = tmp+buffer->getValue(j)*poids->getValue(j, i);            
    }
    state->setValue(i, tmp);
  }        

}


SPTR<Vector> RecurrentModule::getSortie(){
  for (int i=0;i<_taille_sortie;i++){
    sortie->setValue(i, state->getValue(i+_nb_h_neurons));
  }  
  return(sortie);
}

SPTR<Vector> RecurrentModule::getState(){
  return(state);
}

void RecurrentModule::updateState(SPTR<Vector> new_state)
{
  for (int i=0;i<_nb_h_neurons+_taille_sortie;i++)
    {
      state->setValue(i, new_state->getValue(i));
    }
}

void RecurrentModule::initGradient() {
  for(int i =0;i<_taille_entree+_nb_h_neurons+_taille_sortie;i++){
    for(int j=0;j<_nb_h_neurons+_taille_sortie;j++){
      gradient->setValue(i,j, 0.0);
    }
  }
}


void RecurrentModule::updatePoids(double pasGradient) {

  for (int j = 0;j<_taille_entree+_nb_h_neurons+_taille_sortie;j++) 
    {
      for (int i=0;i<_nb_h_neurons+_taille_sortie;i++)
	{
	  poids->setValue(j, i, poids->getValue(j, i) - pasGradient * gradient->getValue(j, i));
	}
    }
}

void RecurrentModule::backward_updateGradient(SPTR<Vector> delta)
{
  for (int j=0;j<_taille_entree+_nb_h_neurons+_taille_sortie;j++)
    {
      for (int i=0;i<_nb_h_neurons+_taille_sortie;i++) 
	{
	  float tmp = 0.0;
	  for (int k=0;k<_nb_h_neurons+_taille_sortie;k++)
	    {
	      tmp = tmp + dynamic_gradient->getValue(j, i, k)*delta->getValue(k);
	    }
	  gradient->setValue(j, i, tmp);
	}
    }
}

void RecurrentModule::computeDynamicGradient(SPTR<Vector> derive_input)
{
  SPTR<Matrix> wtimespt(new Matrix(_taille_entree+_nb_h_neurons+_taille_sortie, _nb_h_neurons+_taille_sortie));

  for (int j=0;j<_taille_entree+_nb_h_neurons+_taille_sortie;j++)
    {
      for (int i=0;i<_nb_h_neurons+_taille_sortie;i++) 
	{
	  float tmp = 0.0;
	  for (int k=0;k<_nb_h_neurons+_taille_sortie;k++)
	    {
	      tmp = tmp+(poids->getValue(k+_taille_entree, i) * array_dynamic_gradient.at(0)->getValue(j, i, k));
	    }
	  wtimespt->setValue(j, i, tmp);
	}
    }	 
   
  float tmp;
  for (int j=0;j<_taille_entree+_nb_h_neurons+_taille_sortie;j++)
    {
      for (int i=0;i<_nb_h_neurons+_taille_sortie;i++) 
	{
	  for (int k=0;k<_nb_h_neurons+_taille_sortie;k++)
	    {
	      if (i != k) {
		tmp = derive_input->getValue(k)*(wtimespt->getValue(j, i));
	      }
	      else {
		tmp = derive_input->getValue(k)*(wtimespt->getValue(j, i) + buffer->getValue(j));
	      }
	      dynamic_gradient->setValue(j, i, k, tmp);	      
	    }
	}
    }
  array_dynamic_gradient.push_back(dynamic_gradient);
  array_dynamic_gradient.pop_front();
}




