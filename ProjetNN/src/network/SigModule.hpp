#ifndef SIGMODULE_HH_
#define SIGMODULE_HH_


#include "../tools/Vector.hpp"
#include "../tools/Matrix.hpp"
#include <math.h>
#include "../tools/smart_ptr.h"
#include "Module.hpp"

class SigModule : public Module {
public: 
  SigModule();
  SigModule(int taille_entree, int taille_sortie);
  virtual ~SigModule();
  
  void forward(SPTR<Vector> entree);
  virtual void backward_computeDeltaInputs(SPTR<Vector> input, SPTR<Vector> deltaOutput);
  virtual SPTR<Vector> getDelta() {return delta;}
  virtual SPTR<Vector> getSortie();
  virtual void initGradient();
  virtual void updatePoids(double pasGradient);
  virtual void backward(SPTR<Vector> input, SPTR<Vector> delta)
  {
    backward_computeDeltaInputs(input, delta);
  }


protected:
  float sigmoid(float x);
  int _taille_entree;
  int _taille_sortie;
  SPTR<Vector> sortie;
  SPTR<Vector> delta;
};


#endif


