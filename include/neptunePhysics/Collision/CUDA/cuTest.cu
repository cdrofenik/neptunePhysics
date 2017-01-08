#include <iostream>

// CUDA runtime
#include <cuda_runtime.h>

using namespace std;

__global__ void AddIntsCUDA(int *a, int *b)
{
	a[0] += b[0];
}

int main()
{
	int a = 5, b = 9;
	int *dev_a, *dev_b;

	cudaMalloc(&dev_a, sizeof(int));
	cudaMalloc(&dev_b, sizeof(int));

	cudaMemcpy(dev_a, &a, sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(dev_a, &a, sizeof(int), cudaMemcpyHostToDevice);

	AddIntsCUDA << <1, 1 >> >(dev_a, dev_b);

	cudaMemcpy(&a, dev_a, sizeof(int), cudaMemcpyDeviceToHost);

	cout << "The result is: " << a << endl;

	// free the memory allocated on the GPU
	cudaFree(&dev_a);
	cudaFree(&dev_b);

	return 0;
}