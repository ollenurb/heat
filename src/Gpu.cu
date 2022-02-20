//
// Created by matteo on 11/19/21.
//
#include "Gpu.cuh"
#include <cstdio>
#define index(x, y) x * device::HEIGHT + y

dim3 dim_block;
dim3 dim_grid;

/*
 * Allocate just the HEIGHT of the simulation on the device
 */
namespace device {
  __device__ unsigned int HEIGHT;
  __device__ unsigned int WIDTH;
}

/*
 * Actually compute on the GPU
 */
__global__ void compute_kernel(Real *device_grid, Real gamma) {
  unsigned int x = blockIdx.x * blockDim.x + threadIdx.x;
  unsigned int y = blockIdx.y * blockDim.y + threadIdx.y;

  if((x > 0 && y > 0) && (x < device::WIDTH-1 && y < device::HEIGHT-1)) {
    unsigned int index = index(x, y);
    device_grid[index] = gamma *
                         (device_grid[index((x-1), y)] + device_grid[index((x+1), y)] +
                         (device_grid[index(x, (y-1))] + device_grid[index(x, (y+1))] -
                         (4 * device_grid[index(x, y)]))) + device_grid[index(x, y)];
  }
}

/*
 * Initialize the Device
 */
Gpu::Gpu(unsigned int w, unsigned int h, Real gamma, Real *host_grid) : HEIGHT(h), WIDTH(w), gamma(gamma) {
  cudaMalloc(&device_grid, w * h * sizeof(Real));
  cudaMemcpyToSymbol(device::HEIGHT, &h, sizeof(unsigned int));
  cudaMemcpyToSymbol(device::WIDTH, &w, sizeof(unsigned int));
  cudaMemcpy(device_grid, host_grid, sizeof(Real) * (WIDTH * HEIGHT), cudaMemcpyHostToDevice);
  dim_block = dim3(10, 10);
  dim_grid = dim3(WIDTH / dim_block.x, HEIGHT / dim_block.y);
}

Gpu::~Gpu() {
  cudaFree(&device_grid);
}

/*
 * Compute one step of simulation, then put the results into the host grid
 */
void Gpu::compute_step(Real *host_grid) {
  compute_kernel<<<dim_grid, dim_block>>>(device_grid, gamma);
  cudaMemcpy(host_grid, device_grid, sizeof(Real) * (WIDTH * HEIGHT), cudaMemcpyDeviceToHost);
}

void Gpu::mem_sync(Real *host_grid) {
  cudaMemcpy(device_grid, host_grid, sizeof(Real) * (WIDTH * HEIGHT), cudaMemcpyHostToDevice);
}
