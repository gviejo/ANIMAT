#ifndef MATRIX_HH_
#define MATRIX_HH_

#include <iostream>
#include <vector>
#include <cassert>

class Matrix
{
protected:
  unsigned int _row_size;
  unsigned int _columns_size;
  float **values;

public:
  Matrix();
  Matrix(unsigned int row_size, unsigned int columns_size)
  {
    _row_size = row_size;
    _columns_size = columns_size;
    values = new float*[_row_size];
    for (unsigned i=0;i<row_size;++i) values[i] = new float[columns_size];
    
  }
  
  void setValue(unsigned int row, unsigned int column, float value)
  {
    assert(row < _row_size);
    assert(column < _columns_size);
    values[row][column] = value;
  }

  float getValue(int row, int column)
  {
    assert(row < _row_size);
    assert(column < _columns_size);
    return values[row][column];
  }

  int getRowSize() { return _row_size;}
  int getColumnSize() { return _columns_size;}
  
};
#endif
