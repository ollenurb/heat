//
// Created by matteo on 11/4/21.
//

#include <iostream>
#include "HeatSimulation.cuh"

int main()
{
  std::cout << "Hello world boys!" << std::endl;
  HeatSimulation simulation(600, 300);
  simulation.run();
}