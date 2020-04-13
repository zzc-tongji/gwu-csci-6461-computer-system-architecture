#include <windows.h>
#include "matrix.h"
#include "timer.h"

void DotProductByCpu(Matrix *input_1, Matrix *input_2, Matrix *output)
{
  int size = output->size;
  int total_size = output->total_size;
  int row;
  int column;
  int result;
  for (int i = 0; i < total_size; i++)
  {
    row = i / size;
    column = i % size;
    result = 0;
    int temp = input_1->data[0];
    for (int j = 0; j < size; j++)
    {
      int x = input_1->data[row * size + j];
      int y = input_2->data[j * size + column];
      result += input_1->data[row * size + j] * input_2->data[j * size + column];
    }
    output->data[i] = result;
  }
}
