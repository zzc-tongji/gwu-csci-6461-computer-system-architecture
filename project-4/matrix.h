#pragma once

class Matrix
{
public:
  int *data;
  int size;
  int total_size;
  Matrix(int size);
  Matrix(int size, int fill);
  ~Matrix();
  void Show();
};
