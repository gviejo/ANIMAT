#include "Expert.hpp"


Expert::Expert(gsl_rng* rgen, int nb_module, int input_size, int output_size, int nb_h_neuron)
{
  _nb_module=nb_module;_input_size=input_size;_output_size=output_size;_nb_h_neurons=nb_h_neuron;
  loss.reset(new Loss(_nb_h_neurons, _output_size));
  
  SPTR<Module> recModule(new RecurrentModule(_input_size, _output_size, _nb_h_neurons));
  recModule->randomize(rgen);
  addModules(recModule);   
  
  //SPTR<Module> tanModule(new TanModule(_nb_h_neurons+_output_size, _nb_h_neurons+_output_size));
  //addModules(tanModule);
  SPTR<Module> sigmodule(new SigModule(_nb_h_neurons+_output_size, _nb_h_neurons+_output_size));
  addModules(sigmodule);
}

void Expert :: addModules(SPTR<Module> m){
	vect.push_back(m);
}

SPTR<Vector> Expert:: getSortie(SPTR<Vector> entree){
  vect[0]->forward(entree);
  vect[1]->forward(vect[0]->getState());
  return(vect[1]->getSortie());
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
  


void Expert::backward(SPTR<Vector> input, SPTR<Vector> output, float proba_gate)
{  
  loss->backward(vect[1]->getSortie(), output, proba_gate);

  vect[1]->backward_computeDerivative(vect[0]->getState());

  vect[0]->backward(vect[1]->getDelta(), loss->getDelta());  
}


double Expert::computeError(SPTR<Vector> input, SPTR<Vector> output)
{
  SPTR<Vector> prediction = getSortie(input);
  //prediction->display();
  loss->computeValue(prediction, output);
  return loss->getValue();
}

void Expert::gradientStep(double epsilon_gradient, SPTR<Vector> input, SPTR<Vector> output, float proba_gate, float epsilon)
{
  vect[0]->initGradient();
  backward(input, output, proba_gate);
  vect[0]->updatePoids(epsilon);
  vect[0]->updateState(vect[1]->getSortie());
}
  
