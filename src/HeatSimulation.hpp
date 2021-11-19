//
// Created by matteo on 11/4/21.
//
#pragma once

#include "Engine.hpp"
#include "Globals.hpp"
#include "Gpu.cuh"


class HeatSimulation : public Engine {
private:
  Real *host_grid;
  Real alpha = 1.0;
  Real gamma;
  Gpu *device;

  /* Simulation-specific functions and constants */
  unsigned int temp_to_rgb(Real temp) const;
  /* Maximum&Minimum allowed temperatures by the simulator */
  Real MAX_TEMP = 100.0;
  Real MIN_TEMP = 0.0;
  /* Define maximum hot/cold color */
  const SDL_Color hot_color = {3, 157, 252, SDL_ALPHA_OPAQUE};
  const SDL_Color cold_color = {252, 94, 3, SDL_ALPHA_OPAQUE};

public:
  HeatSimulation(int, int);
  ~HeatSimulation();
  void step() override;
  void render() override;
};