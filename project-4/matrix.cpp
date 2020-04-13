#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

Matrix::Matrix(int size)
{
  this->size = size;
  total_size = size * size;
  data = (int *)malloc(total_size * sizeof(int));
  if (data == NULL)
  {
    throw "memory not allocated";
  }
  srand((unsigned int)(time(NULL)));
  for (int i = 0; i < total_size; i++)
  {
    data[i] = rand() % 100;
  }
}

Matrix::Matrix(int size, int fill)
{
  this->size = size;
  total_size = size * size;
  data = (int *)malloc(total_size * sizeof(int));
  if (data == NULL)
  {
    throw "memory not allocated";
  }
  for (int i = 0; i < total_size; i++)
  {
    data[i] = fill;
  }
}

Matrix::~Matrix()
{
  free(data);
}

void Matrix::Show()
{
  for (int i = 0; i < total_size; i++)
  {
    fprintf(stdout, "%7d", data[i]);
    if (i % size == size - 1)
    {
      fprintf(stdout, "\n");
    }
  }
}
