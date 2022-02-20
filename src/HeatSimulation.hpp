//
// Created by matteo on 11/4/21.
//
#pragma once

#include "Engine.hpp"
#include "Globals.hpp"
#include "Gpu.cuh"
#include <vector>

class HeatSimulation : public Engine {
private:
  Real *host_grid;
  Real alpha = 1.0;
  Real gamma;
  Gpu *device{};

  /* I still need to figure it out */
  /* Simulation-specific functions and constants */
  unsigned int temp_to_rgb(Real temp) const;
  void _render();

  /* Maximum&Minimum allowed temperatures by the simulation */
  Real MAX_TEMP = 100.0;
  Real MIN_TEMP = 0.0;

  /* Define maximum hot/cold color */
  const SDL_Color hot_color = {3, 157, 252, SDL_ALPHA_OPAQUE};
  const SDL_Color cold_color = {252, 94, 3, SDL_ALPHA_OPAQUE};

public:
  HeatSimulation(int, int);
  ~HeatSimulation();
  void set_temp_data(const std::vector<std::tuple<int, int, Real>>& temp_data);
  void step() override;
  void render() override;
};