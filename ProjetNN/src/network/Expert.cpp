#include "Expert.hpp"

Expert::Expert(int dimOutput){
	loss.reset(new Loss(dimOutput));
}

Expert::Expert(gsl_rng* rgen, int nb_module, int input_size, int output_size, int nb_h_neuron)
{
  _nb_module=nb_module;_input_size=input_size;_output_size=output_size;_nb_h_neurons=nb_h_neuron;
  loss.reset(new Loss(_output_size));

  SPTR<Module> mInput(new Module(input_size, _output_size));
  mInput->randomize(rgen);
  addModules(mInput);
  SPTR<Module> mtan(new TanModule(_output_size,_nb_h_neurons));
  addModules(mtan);
  
  if (_nb_module > 2) {
    for (int i = 2; i < _nb_module;i++)
      {
	SPTR<Module> m(new Module(_nb_h_neurons, _nb_h_neurons));
	m->randomize(rgen);
	addModules(m);
        SPTR<Module> mTan(new TanModule(_nb_h_neurons,_nb_h_neurons));
  	addModules(mTan);
      }
  }
  SPTR<Module> mOutput(new Module(_nb_h_neurons, _output_size));
  mOutput->randomize(rgen);
  addModules(mOutput);
  SPTR<Module> mTanFinal(new TanModule(_output_size,_output_size));
  addModules(mTanFinal);
}

void Expert :: addModules(SPTR<Module> m){
	vect.push_back(m);
}

SPTR<Vector> Expert:: getSortie(SPTR<Vector> entree){
  vect[0]->forward(entree);

  for(int i=1; i<vect.size();i++){
    vect[i]->forward(vect[i-1]->getSortie());
  }

  int idx=vect.size()-1;
  return(vect[idx]->getSortie());
}

SPTR<Module> Expert::getModule(int i){
	return(vect[i]);
}

SPTR<Vector> Expert::forward(SPTR<Vector> input, SPTR<Vector> output){
  
  SPTR<Vector> prediction = getSortie(input);
  loss->computeValue(prediction, output);
  return prediction;

}

SPTR<Loss> Expert:: getLoss(){
	return loss;
}
  

void Expert::initGradient()
{
  for (int i=0;i<vect.size();i++)
    {
      vect[i]->initGradient();
    }
};

void Expert::backward(SPTR<Vector> input, SPTR<Vector> output, float proba_gate)
{
  int nb_modules = vect.size();

  
  loss->backward(vect[nb_modules-1]->getSortie(), output, proba_gate);

  if (nb_modules>1)
    vect[nb_modules-1]->backward(vect[nb_modules-2]->getSortie(), loss->getDelta());
   
  else 
    vect[nb_modules-1]->backward_updateGradient(input, loss->getDelta());


  
  for (int i = 1; i < nb_modules; i++)
    {
      int nbm = nb_modules-i-1;
      if (nbm==0)
	vect[nbm]->backward_updateGradient(input, vect[nbm+1]->getDelta());
      else 	
	vect[nbm]->backward(vect[nbm-1]->getSortie(), vect[nbm+1]->getDelta());
    }
  
}

void Expert::updateGradient(double epsilon)
{
  for (int i = 0;i<vect.size();i++)
    vect[i]->updatePoids(epsilon);
}


void Expert::gradientStep(double epsilon_gradient, SPTR<Vector> input, SPTR<Vector> output, float proba_gate, float epsilon, float eta)
{
  initGradient();
  backward(input, output, proba_gate);
  updateGradient(epsilon);
  
}

double Expert::computeError(SPTR<Vector> input, SPTR<Vector> output)
{
  SPTR<Vector> prediction = getSortie(input);
  loss->computeValue(prediction, output);
  return loss->getValue();
}

  
