//
// Created by matteo on 11/4/21.
//
#include <iostream>
#include "HeatSimulation.hpp"
#include "../lib/csv.h"

#define SIMULATION_WIDTH 1000
#define SIMULATION_HEIGHT 600

std::vector<std::tuple<int, int, Real>> load_csv_data(const std::string& path) {
  io::CSVReader<3> in(path);
  in.read_header(io::ignore_extra_column, "x", "y", "temp");
  int x, y;
  Real temp;
  std::vector<std::tuple<int, int, Real>> result;
  while(in.read_row(x, y, temp)) {
    result.emplace_back(x, y, temp);
  }
  return result;
}

int main(int argc, char** arg) {
  if(argc > 1) {
    std::string path(arg[1]);
    HeatSimulation simulation(SIMULATION_WIDTH, SIMULATION_HEIGHT);
    simulation.set_temp_data(load_csv_data(path));
    simulation.start();
  } else {
    std::cout << "Error: CSV file path not supplied" << std::endl
              << "Usage: heat-simulation CSV_PATH" << std::endl;
  }
}