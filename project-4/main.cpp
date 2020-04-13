#include <conio.h>
#include <stdio.h>
#include "calculate.h"
#include "cuda_helper.h"
#include "matrix.h"
#include "timer.h"

void GPUWarmUp()
{
  Matrix m(16, 0);
  Matrix n(16, 0);
  Matrix r_cpu(16, 0);
  Matrix r_gpu(16, 0);
  DotProductByGpu(&m, &n, &r_cpu);
}

void SplitLine()
{
  printf("----------------------------------------\n\n");
}

void ShowMatrix(char *name, Matrix *data)
{
  fprintf(stdout, "[%s]\n", name);
  data->Show();
  fprintf(stdout, "\n");
}

void Homework()
{
  // prepare
  Timer timer = Timer();
  printf("size = 16x16\n\n");
  Matrix m(16, 1);
  Matrix n(16, 2);
  Matrix r_cpu(16, 0);
  Matrix r_gpu(16, 0);
  // CPU
  timer.start();
  DotProductByCpu(&m, &n, &r_cpu);
  timer.stop();
  printf("[CPU]\n");
  timer.show();
  // GPU
  timer.start();
  DotProductByGpu(&m, &n, &r_gpu);
  timer.stop();
  printf("[GPU]\n");
  timer.show();
  // show data
  ShowMatrix("m", &m);
  ShowMatrix("n", &n);
  ShowMatrix("r_cpu", &r_cpu);
  ShowMatrix("r_gpu", &r_gpu);
  SplitLine();
  fflush(stdout);
}

int main(int argc, char **argv)
{
  GPUWarmUp();
  SplitLine();
  CudaDeviceList();
  SplitLine();
  Homework();
  Timer timer = Timer();
  for (int size = 1; size <= 32768; size *= 2)
  {
    // prepare
    printf("size = %dx%d\n\n", size, size);
    Matrix m(size);
    Matrix n(size);
    Matrix r_cpu(size, 0);
    Matrix r_gpu(size, 1);
    // CPU
    timer.start();
    DotProductByCpu(&m, &n, &r_cpu);
    timer.stop();
    printf("[CPU]\n");
    timer.show();
    // GPU
    timer.start();
    DotProductByGpu(&m, &n, &r_gpu);
    timer.stop();
    printf("[GPU]\n");
    timer.show();
    // show data
    if (size <= 8)
    {
      ShowMatrix("m", &m);
      ShowMatrix("n", &n);
      ShowMatrix("r_cpu", &r_cpu);
      ShowMatrix("r_gpu", &r_gpu);
    }
    SplitLine();
    fflush(stdout);
  }
  printf("Press any key to continue.\n");
  getch();
  return 0;
}
