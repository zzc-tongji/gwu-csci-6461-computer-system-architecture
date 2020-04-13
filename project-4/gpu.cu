#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "calculate.h"
#include "cuda_helper.h"
#include "matrix.h"

__global__ void KernelDotProduct(int *in_1, int *in_2, int size, int *out)
{
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  int total_size = size * size;
  if (index >= total_size)
  {
    return;
  }
  int row = index / size;
  int column = index % size;
  int result = 0;
  for (int i = 0; i < size; i++)
  {
    result += in_1[row * size + i] * in_2[i * size + column];
  }
  out[index] = result;
}

void DotProductByGpu(Matrix *input_1, Matrix *input_2, Matrix *output)
{
  int size = output->size;
  int total_size = output->total_size;
  CudaErrorHandler(cudaSetDevice(0));
  // allocate
  int *in_1 = NULL;
  int *in_2 = NULL;
  int *out = NULL;
  CudaErrorHandler(cudaMalloc(&in_1, total_size * sizeof(int)));
  CudaErrorHandler(cudaMalloc(&in_2, total_size * sizeof(int)));
  CudaErrorHandler(cudaMalloc(&out, total_size * sizeof(int)));
  // host => device
  CudaErrorHandler(cudaMemcpy(in_1, input_1->data, total_size * sizeof(int), cudaMemcpyKind::cudaMemcpyHostToDevice));
  CudaErrorHandler(cudaMemcpy(in_2, input_2->data, total_size * sizeof(int), cudaMemcpyKind::cudaMemcpyHostToDevice));
  // Launch a kernel on the GPU with one thread for each element.
  KernelDotProduct<<<total_size / 1024 + 1, 1024>>>(in_1, in_2, size, out);
  // Check for any errors launching the kernel
  CudaErrorHandler(cudaGetLastError());
  // host <= device
  CudaErrorHandler(cudaMemcpy(output->data, out, total_size * sizeof(int), cudaMemcpyKind::cudaMemcpyDeviceToHost));
  // synchronize
  CudaErrorHandler(cudaDeviceSynchronize());
}
