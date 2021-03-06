#include "../tools/smart_ptr.h"
#include "Layer.hpp"
#include <math.h>


SPTR<Expert> Layer::getExpert(int i)
{
  return _layer[i];
}

void Layer::forward(SPTR<Vector> input, SPTR<Vector> output)
{
  for (int i=0;i<_nb_expert;i++)
    {
      _output[i] = _layer[i]->forward(input, output);
    }
}


SPTR<Vector> Layer::getOutput(int i)
{
  return _output[i];
}

void Layer::computeErrorLayer(SPTR<Vector> input, SPTR<Vector> output)
{
  for(int i=0; i< _nb_expert;i++)
  {
    std::cout << _layer[i]->computeError(input, output) << "   " ; 
  }
}


void Layer::computeGate()
{
  float sum_exp_state = 0.0;
  float max = 0.0;
  for (int i = 0; i<_nb_expert;i++)
    {
      _exp_state->setValue(i, exp(_state->getValue(i)));
      sum_exp_state = sum_exp_state + _exp_state->getValue(i);
    }
  for (int i = 0; i<_nb_expert;i++)
    {
      _gate->setValue(i, _exp_state->getValue(i)/sum_exp_state);     
      _plot->push(i, _gate->getValue(i));
      
      if(_gate->getValue(i)>max){
	max=_gate->getValue(i);
	best=i;
      }
    }
  
}
  
void Layer::computePropaGate()
{
  float big_sum = 0.0;
  SPTR<Vector> tmp(new Vector(_nb_expert));
  for (int i = 0; i<_nb_expert;i++)
    {
      float delta = _layer[i]->getLoss()->getValue();
      tmp->setValue(i, _gate->getValue(i)*exp(-delta/2*pow(_sigma, 2)));
      big_sum = big_sum + tmp->getValue(i);
    }
 
  for (int i =0; i<_nb_expert;i++)
    {
      _proba_gate->setValue(i, tmp->getValue(i)/big_sum);

    }

}

void Layer::computeGradientState()
{
  for(int i =0;i<_nb_expert;i++){
    _grad->setValue(i,_proba_gate->getValue(i)-_gate->getValue(i));
  }
}

void Layer::updateState(){
  computeGradientState();

  for(int i=0;i<_nb_expert;i++)
    {    
      float tmp = _epsilon*_grad->getValue(i)-_eta*(array_state.back()->getValue(i)-array_state.front()->getValue(i));
      _state->setValue(i, _state->getValue(i)+tmp);

    }
  array_state.pop();
  array_state.push(_state);
  
}


void Layer::backwardLayer(int it, float epsilon_gradient, SPTR<Vector> input, SPTR<Vector> output)
{
  forward(input, output);
  computeGate(); _plot->update(0);
  computePropaGate();
  
  for (int i = 0; i < _nb_expert ; i++) 
    {

      _layer[i]->gradientStep(epsilon_gradient, input, output, _proba_gate->getValue(i), _epsilon, _eta);
    }
  
  if (it%1 == 0)
    {

      updateState();
    }
}

int Layer::getBest(){
return best;
}
