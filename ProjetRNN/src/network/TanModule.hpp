#ifndef TANMODULE_HH_
#define TANMODULE_HH_

//#include <iostream>
#include "../tools/Vector.hpp"
#include "../tools/Matrix.hpp"
#include "../tools/smart_ptr.h"
//#include <gsl/gsl_sf.h>
//#include <gsl/gsl_randist.h>
//#include <gsl/gsl_cdf.h>
//#include <gsl/gsl_statistics_double.h>
#include "Module.hpp"

class TanModule : public Module {
public: 
  TanModule();
  TanModule(int taille_entree, int taille_sortie);
  virtual ~TanModule();
  
  void forward(SPTR<Vector> entree);
  virtual void backward_computeDeltaInputs(SPTR<Vector> input, SPTR<Vector> deltaOutput);
  virtual void backward_computeDerivative(SPTR<Vector> input);
  virtual SPTR<Vector> getDelta() {return delta;}
  virtual SPTR<Vector> getSortie();
  virtual void initGradient();
  virtual void updatePoids(double pasGradient);
  virtual void backward(SPTR<Vector> input, SPTR<Vector> delta)
  {
    backward_computeDeltaInputs(input, delta);
  }


protected:
  float tan(float x);
  int _taille_entree;
  int _taille_sortie;
  SPTR<Vector> sortie;
  SPTR<Vector> delta;
};


#endif


