#include <iostream>
#include <cmath>

using namespace std;

__global__ void		kernel(double *arr, int n)
{
	int index, offset;
	index = blockDim.x * blockIdx.x + threadIdx.x;
	offset = blockDim.x * gridDim.x;
	for (int i = index; i < n; i += offset)
		arr[i] = abs(arr[i]);
}

int		main(void)
{
	int		n;
	double  *arr;

	cin >> n;
	arr = (double *)malloc(n * sizeof(double));
	for (int i = 0; i < n; ++i)
		cin >> arr[i];

	double	*dev_arr;
	cudaMalloc(&dev_arr, sizeof(double) * n);
	cudaMemcpy(dev_arr, arr, sizeof(double) * n, cudaMemcpyHostToDevice);

	kernel<<<256, 256>>>(dev_arr, n);

	cudaMemcpy(arr, dev_arr, sizeof(double) * n, cudaMemcpyDeviceToHost);
	cudaFree(dev_arr);
	for (int i = 0; i < n; ++i)
		printf("%.10e ", arr[i]);
	printf("\n");
	free(arr);
	return (0);
}
