#pragma once

#include <windows.h>
#include "matrix.h"

void DotProductByCpu(Matrix *input_1, Matrix *input_2, Matrix *output);

void DotProductByGpu(Matrix *input_1, Matrix *input_2, Matrix *output);
