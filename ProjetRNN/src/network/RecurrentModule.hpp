#ifndef RECURRENTMODULE_HH_
#define RECURRENTMODULE_HH_

#include "../tools/Vector.hpp"
#include "../tools/Matrix.hpp"
#include "../tools/Matrix3D.hpp"
#include "../tools/smart_ptr.h"
#include "Module.hpp"
#include <deque>

class RecurrentModule : public Module {
public: 
  RecurrentModule();
  RecurrentModule(int taille_entree, int taille_sortie, int nb_h_neurons);
  virtual ~RecurrentModule();
  
  void randomize(gsl_rng* rgen);
  void forward(SPTR<Vector> entree);
  virtual void backward_updateGradient(SPTR<Vector> delta);
  void computeDynamicGradient(SPTR<Vector> derive_input);
  virtual SPTR<Vector> getSortie();
  virtual SPTR<Vector> getState();
  virtual void updateState(SPTR<Vector> new_state);
  virtual void initGradient();
  virtual void updatePoids(double pasGradient);
  virtual void backward(SPTR<Vector> derive_input, SPTR<Vector> delta)
  {
    computeDynamicGradient(derive_input);
    backward_updateGradient(delta);
  };


protected:
  int _taille_entree;
  int _taille_sortie;
  int _nb_h_neurons;
  SPTR<Vector> buffer;
  SPTR<Vector> sortie;
  SPTR<Vector> state;
  SPTR<Vector> delta;
  SPTR<Matrix> poids;
  SPTR<Matrix> gradient;
  std::deque< SPTR<Matrix3D> > array_dynamic_gradient;
  SPTR<Matrix3D> dynamic_gradient;
  
};


#endif


