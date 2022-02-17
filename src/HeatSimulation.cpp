//
// Created by matteo on 11/4/21.
//
#include <algorithm>
#include "HeatSimulation.hpp"

/* Translate a 2D index to a 1D index */
#define index(x, y) x * HEIGHT + y

/*
 * HeatSimulation constructor
 */
HeatSimulation::HeatSimulation(int w, int h) : Engine(w, h) {
  gamma = (alpha * 1.0f)/(4.0f * alpha); // gamma = (alpha * dt) / (4 * alpha)
  host_grid = new Real[w * h];

  // TODO: TO remove
  // Initialize the grid
  for(int i = 0; i < w * h; i++) {
    host_grid[i] = 0.0f;
    if (i > 100 && i < 200) host_grid[i] = 100.0f;
  }

#ifdef GPU_ENABLED
  device = new Gpu(w, h, gamma, host_grid);
#endif
}

HeatSimulation::~HeatSimulation() {
  free(host_grid);
#ifdef GPU_ENABLED
  free(device);
#endif
}

/*
 * Gets called by the Engine at every render step
 * The screen is an SDL_Texture object
 */
void HeatSimulation::render() {
  void *pixels;
  int pitch;
  Uint32 *dest;

  if (SDL_LockTexture(screen, nullptr, &pixels, &pitch) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't lock texture: %s\n", SDL_GetError());
  }

  for (int y = 0; y < HEIGHT; y++) {
    dest = (Uint32 *) ((Uint8 *) pixels + y * pitch);
    for (int x = 0; x < WIDTH; x++) {
      *(dest + x) = temp_to_rgb(host_grid[index(x, y)]);
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
#ifdef GPU_ENABLED
   device->compute_step(host_grid);
#else
  for(int x = 1; x < WIDTH-1; x++) {
    for(int y = 1; y < HEIGHT-1; y++) {
      host_grid[index(x, y)] = gamma *
              (host_grid[index((x-1), y)] + host_grid[index((x+1), y)] +
              (host_grid[index(x, (y-1))] + host_grid[index(x, (y+1))] -
              (4 * host_grid[index(x, y)]))) + host_grid[index(x, y)];
    }
  }
#endif
}

/*
 * Compute the corresponding RGB color given a temperature value
 */
unsigned int HeatSimulation::temp_to_rgb(Real temp) const {
  Real norm_temp = (temp - MIN_TEMP / (MAX_TEMP - MIN_TEMP));
  Real r_val = (Real) (cold_color.r - hot_color.r) * norm_temp + hot_color.r;
  Real g_val = (Real) (cold_color.g - hot_color.g) * norm_temp + hot_color.g;
  Real b_val = (Real) (cold_color.b - hot_color.b) * norm_temp + hot_color.b;

  unsigned r = std::floor(std::clamp<Real>(r_val, 0, 255));
  unsigned g = std::floor(std::clamp<Real>(g_val, 0, 255));
  unsigned b = std::floor(std::clamp<Real>(b_val, 0, 255));
  return (0xFF000000 | (r << 16) | (g << 8) | b);
}
