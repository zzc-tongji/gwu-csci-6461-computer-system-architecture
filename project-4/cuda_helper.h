#pragma once

#include "cuda_runtime.h"

int CudaDeviceList();

void CudaErrorHandler(cudaError_t error);
