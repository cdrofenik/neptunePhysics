#include <iostream>

// CUDA runtime
#include <cuda_runtime.h>

namespace NeptunePhysics
{
	__global__ void AddIntsCUDA(int *a, int *b)
	{
		a[0] += b[0];
	}

	extern "C" int cuda_func(int &a, const int &b)
	{
		int *dev_a, *dev_b;

		cudaMalloc(&dev_a, sizeof(int));
		cudaMalloc(&dev_b, sizeof(int));

		cudaMemcpy(dev_a, &a, sizeof(int), cudaMemcpyHostToDevice);
		cudaMemcpy(dev_b, &b, sizeof(int), cudaMemcpyHostToDevice);

		AddIntsCUDA << <1, 1 >> >(dev_a, dev_b);

		cudaMemcpy(&a, dev_a, sizeof(int), cudaMemcpyDeviceToHost);

		std::cout << "The result is: " << a << std::endl;

		// free the memory allocated on the GPU
		cudaFree(&dev_a);
		cudaFree(&dev_b);

		return a;
	}
}