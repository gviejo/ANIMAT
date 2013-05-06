#ifndef VECTOR_HH_
#define VECTOR_HH_

#include <iostream>
#include <gsl/gsl_sf.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_statistics_double.h>

  
class Vector 
{
protected:
  int _size;
  float *values;
  
public:
  Vector();
  Vector(int size) 
  {
    _size = size;
    values = new float[_size];
  }
  
  void setValue(int i, float value)
  {
    values[i] = value;
  }

  float getValue(int i)
  {
    return values[i];
  }

  int size()
  {
    return _size;
  }
  void fill_random_vector(gsl_rng* rgen) 
  {
    for (int i = 0; i< _size ; i++) {
      float tmp =float(gsl_ran_flat(rgen, 0, 1));
      setValue(i, tmp);
      //std::cout << tmp << " ";
    }
    //std::cout << std::endl;
  }

  void fill_random_vector(gsl_rng* rgen, double sigma)
  {
    for (int i = 0; i<_size;i++) {
      float tmp = float(gsl_ran_gaussian(rgen, sigma));
      setValue(i, tmp);
    }
  }
  
  void display()
  {
    for (int i = 0; i<_size;i++)
      std::cout << values[i] << " ";
    std::cout << std::endl;
  }
  
  int getMax()
  {
    return values[getMaxIndex()];
  }
  
  int getMaxIndex()
  {
    float tmp = -10000000;
    for (int i =0;i<_size;i++){
      if (values[i] > tmp)
	values[i] = tmp;
    }
  }

  float sum()
  {
    float tmp = 0.0;
    for (int i = 0;i<_size;i++)
      tmp = tmp+values[i];
    return tmp;
  }

  float sum(int start, int end)
  {
    float tmp = 0.0;
    for (int i = start;i<end;i++)
      tmp = tmp+values[i];
    return tmp;
  }

  void initialisationZero()
  {
    for (int i=0;i<_size;i++)
      {
	values[i] = 0.0;
      }
  }
  
};
#endif
