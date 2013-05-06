#ifndef MODULE_HH_
#define MODULE_HH_

#include <iostream> 
#include "../tools/Vector.hpp"
#include "../tools/Matrix.hpp"
#include "../tools/smart_ptr.h"
#include <gsl/gsl_sf.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_statistics_double.h>
		    
class Module {
public: 
  Module();
  virtual ~Module();

  Module(int taille_entree, int taille_sortie)
  {
    _taille_entree = taille_entree;
    _taille_sortie = taille_sortie;
    poids.reset(new Matrix(_taille_entree,_taille_sortie));
    gradient.reset(new Matrix(_taille_entree,_taille_sortie));
    sortie.reset(new Vector(_taille_sortie));
    delta.reset(new Vector(_taille_entree));
  }

  virtual void forward(SPTR<Vector> entree);
  virtual void backward_computeDeltaInputs(SPTR<Vector> input, SPTR<Vector> deltaOutput);
  virtual SPTR<Vector> getDelta() { return delta;}  
  virtual SPTR<Vector> getSortie();
  virtual void randomize(gsl_rng* rgen);
  virtual void backward_updateGradient(SPTR<Vector> input, SPTR<Vector> deltaOutput);
  virtual void initGradient();
  virtual void updatePoids(double pasGradient);

  virtual void backward(SPTR<Vector> input, SPTR<Vector> delta)
  {
    backward_updateGradient(input, delta);
    backward_computeDeltaInputs(input, delta);
  }

protected:
  SPTR<Matrix> poids;
  SPTR<Matrix> gradient;
  SPTR<Vector> sortie;
  SPTR<Vector> delta;
 
  int _taille_entree;
  int _taille_sortie;

};


#endif
