//
// Created by matteo on 11/4/21.
//

#include "HeatSimulation.cuh"

/* Translate a 2D index to a 1D index */
#define index(x, y) x * HEIGHT + y

/*
 * Construct a HeatSimulation
 */
HeatSimulation::HeatSimulation(int w, int h) : Engine(w, h) {
  host_grid = new Real[w * h];
  cudaMalloc(&device_grid, w * h * sizeof(Real));
}

HeatSimulation::~HeatSimulation() {
  free(host_grid);
  cudaFree(&device_grid);
}

/*
 * Gets called by the Engine at every render step
 * The screen is an SDL_Texture object
 * TODO: Refactor
 */
void HeatSimulation::render() {
  void *pixels;
  int pitch;
  Uint32 *dest;
  Real b;

  if (SDL_LockTexture(screen, nullptr, &pixels, &pitch) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't lock texture: %s\n", SDL_GetError());
  }

  for (int y = 0; y < HEIGHT; y++) {
    dest = (Uint32 *) ((Uint8 *) pixels + y * pitch);
    for (int x = 0; x < WIDTH; x++) {
//      b = std::min(host_grid[index(x, y)], static_cast<Real>(1));
//      *(dest + x) = utils::HSBtoRGB(0.5, 1, b);
    }
  }
  SDL_UnlockTexture(screen);
}

/*
 * Gets called by the Engine at every simulation step
 * We need to calculate the temperature state at t + \delta t
 * Since I'm assuming that \delta x = \delta y = 1 to simplify things, then
 * to calculate T(x, y, t + \delta t ) = T(x, y - 1) + T(x - 1, y) - 4T(x, y) + T(x, y + 1) + T(x + 1, y)
 * Source:
 * http://www.u.arizona.edu/~erdmann/mse350/_downloads/2D_heat_equation.pdf
 */
void HeatSimulation::step() {

}

__global__ void step_kernel(Real *device_grid) {

}

