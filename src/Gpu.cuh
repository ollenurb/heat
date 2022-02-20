//
// Created by matteo on 11/19/21.
//
#pragma once
#include "Globals.hpp"

/*
 * Abstract away device-specific implementation details
 */
class Gpu {
private:
  unsigned int WIDTH;
  unsigned int HEIGHT;
  Real gamma;
  Real *device_grid = nullptr;

public:
  Gpu(unsigned int, unsigned int, Real, Real*);
  ~Gpu();
  void compute_step(Real *);
  void mem_sync(Real *host_grid);
};
