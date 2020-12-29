#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

#define CSC(call)  													\
do {																\
	cudaError_t res = call;											\
	if (res != cudaSuccess) {										\
		fprintf(stderr, "ERROR in %s:%d. Message: %s\n",			\
				__FILE__, __LINE__, cudaGetErrorString(res));		\
		exit(0);													\
	}																\
} while(0)

texture<uchar4, 2, cudaReadModeElementType> tex;

__global__	void	kernel(uchar4* out, int w, int h)
{
	int idx = blockDim.x * blockIdx.x + threadIdx.x;
	int idy = blockDim.y * blockIdx.y + threadIdx.y;
	int offsetx = blockDim.x * gridDim.x;
	int offsety = blockDim.y * gridDim.y;

	for (int y = idy; y < h; y += offsety)
		for (int x = idx; x < w; x += offsetx)
		{
			double Gx = 0.0;
			double Gy = 0.0;
			uchar4 pixel;

			pixel = tex2D(tex, x - 1, y - 1);
			Gx -= (0.299 * pixel.x) + (0.587 * pixel.y) + (0.114 * pixel.z);
			pixel = tex2D(tex, x - 1, y);
			Gx -= (0.299 * pixel.x) + (0.587 * pixel.y) + (0.114 * pixel.z);
			pixel = tex2D(tex, x - 1, y + 1);
			Gx -= (0.299 * pixel.x) + (0.587 * pixel.y) + (0.114 * pixel.z);
			pixel = tex2D(tex, x + 1, y - 1);
			Gx += (0.299 * pixel.x) + (0.587 * pixel.y) + (0.114 * pixel.z);
			pixel = tex2D(tex, x + 1, y);
			Gx += (0.299 * pixel.x) + (0.587 * pixel.y) + (0.114 * pixel.z);
			pixel = tex2D(tex, x + 1, y + 1);
			Gx += (0.299 * pixel.x) + (0.587 * pixel.y) + (0.114 * pixel.z);

			pixel = tex2D(tex, x - 1, y - 1);
			Gy -= (0.299 * pixel.x) + (0.587 * pixel.y) + (0.114 * pixel.z);
			pixel = tex2D(tex, x, y - 1);
			Gy -= (0.299 * pixel.x) + (0.587 * pixel.y) + (0.114 * pixel.z);
			pixel = tex2D(tex, x + 1, y - 1);
			Gy -= (0.299 * pixel.x) + (0.587 * pixel.y) + (0.114 * pixel.z);
			pixel = tex2D(tex, x - 1, y + 1);
			Gy += (0.299 * pixel.x) + (0.587 * pixel.y) + (0.114 * pixel.z);
			pixel = tex2D(tex, x, y + 1);
			Gy += (0.299 * pixel.x) + (0.587 * pixel.y) + (0.114 * pixel.z);
			pixel = tex2D(tex, x + 1, y + 1);
			Gy += (0.299 * pixel.x) + (0.587 * pixel.y) + (0.114 * pixel.z);

			unsigned char grad = (unsigned char)min((int)sqrt(Gx * Gx + Gy * Gy), (int)0xFF);

			out[y * w + x] = make_uchar4(grad, grad, grad, 0);
		}
}

int		main(void)
{
	int		w, h;
	char path_in[256];
	char path_out[256];

	scanf("%s", path_in);
	scanf("%s", path_out);
	FILE *fp = fopen(path_in, "rb");
	fread(&w, sizeof(int), 1, fp);
	fread(&h, sizeof(int), 1, fp);
	uchar4 *data = (uchar4 *)malloc(sizeof(uchar4) * w * h);
	fread(data, sizeof(uchar4), w * h, fp);
	fclose(fp);

	cudaArray	*arr;
	cudaChannelFormatDesc ch = cudaCreateChannelDesc<uchar4>();
	CSC(cudaMallocArray(&arr, &ch, w, h));
	CSC(cudaMemcpyToArray(arr, 0, 0, data, sizeof(uchar4) * w * h, cudaMemcpyHostToDevice));

	tex.addressMode[0] = cudaAddressModeClamp;
	tex.addressMode[1] = cudaAddressModeClamp;
	tex.channelDesc = ch;
	tex.filterMode = cudaFilterModePoint;
	tex.normalized = false;

	CSC(cudaBindTextureToArray(tex, arr, ch));

	uchar4 *dev_out;
	CSC(cudaMalloc(&dev_out, sizeof(uchar4) * w * h));

	kernel<<<dim3(16, 16), dim3(16, 16)>>>(dev_out, w, h);
	CSC(cudaGetLastError());

	CSC(cudaMemcpy(data, dev_out, sizeof(uchar4) * w * h, cudaMemcpyDeviceToHost));
	CSC(cudaUnbindTexture(tex));

	CSC(cudaFreeArray(arr));
	CSC(cudaFree(dev_out));

	fp = fopen(path_out, "wb");
	fwrite(&w, sizeof(int), 1, fp);
	fwrite(&h, sizeof(int), 1, fp);
	fwrite(data, sizeof(uchar4), w * h, fp);
	fclose(fp);

	free(data);
	return 0;
}
