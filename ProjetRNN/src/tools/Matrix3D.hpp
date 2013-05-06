#ifndef MATRIX3D_HH_
#define MATRIX3D_HH_

#include <iostream>
#include <vector>
#include <cassert>

class Matrix3D
{
protected:
  unsigned int _row_size;
  unsigned int _columns_size;
  unsigned int _depth_size;
  float ***values;

public:
  Matrix3D();
  Matrix3D(unsigned int row_size, unsigned int columns_size, unsigned int depth_size)
  {
    _row_size = row_size;
    _columns_size = columns_size;
    _depth_size = depth_size;
    values = new float**[_row_size];
    for (int i=0;i<row_size;i++) 
      {
	values[i] = new float*[_columns_size];
	for (int j=0;j<_columns_size;j++) 
	  {
	    values[i][j] = new float[_depth_size];
	    for (int k=0;k<_depth_size;k++) 
	      {
		values[i][j][k] = 0.0;
		
	      }
	  }
      }
  }
  
  void setValue(unsigned int row, unsigned int column, unsigned int depth, float value)
  {
    assert(row < _row_size);
    assert(column < _columns_size);
    assert(column < _depth_size);
    values[row][column][depth] = value;
  }

  float getValue(int row, int column, int depth)
  {
    assert(row < _row_size);
    assert(column < _columns_size);
    assert(depth < _depth_size);
    return values[row][column][depth];
  }

  int getRowSize() { return _row_size;}
  int getColumnSize() { return _columns_size;}
  int getDepthSize() { return _row_size;}
  
};
#endif
