//
// Created by matteo on 11/4/21.
//
#pragma once

#include "Engine.hpp"

class HeatSimulation : public Engine {
public:
  HeatSimulation(int w, int h) : Engine(w, h) { }
  void step() override;
  void render() override;
};