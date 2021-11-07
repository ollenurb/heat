//
// Created by matteo on 11/4/21.
//
#pragma once

#include "Engine.hpp"

/* Define precision */
typedef float Real;

class HeatSimulation : public Engine {
private:
  Real *device_grid;
  Real *host_grid;
  Real alpha = 1.0;
public:
  HeatSimulation(int, int);
  ~HeatSimulation();
  void step() override;
  void render() override;
};