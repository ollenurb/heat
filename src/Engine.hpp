//
// Created by matteo on 11/4/21.
//
#pragma once

#include "SDL.h"

class Engine {
// Screen should be able to be accessed by the implementation specific code
protected:
  SDL_Texture *screen;

private:
  // Engine-related variables
  const int WIDTH;
  const int HEIGHT;
  bool running;

  // SDL-specific references
  SDL_Window *window;
  SDL_Renderer *renderer;

  // Engine-related functions
  void process_events();
  void render(SDL_Texture*);

public:
  Engine(int, int);
  ~Engine();
  void run();

  // Simulation-Specific functions
  virtual void step() = 0;
  virtual void render() = 0;
};
