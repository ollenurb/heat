//
// Created by matteo on 11/4/21.
//
#pragma once

#include "SDL.h"

class Engine {
// Screen should be able to be accessed by the implementation specific code
protected:
  SDL_Texture *screen;
  // Engine-related variables
  const int WIDTH;
  const int HEIGHT;

private:
  bool open = false;
  bool running = false;
  // SDL-specific references
  SDL_Window *window{};
  SDL_Renderer *renderer{};

  // Engine-related functions
  void process_events();
  void handle_key(SDL_Keycode);

public:
  Engine(int, int);
  ~Engine();
  void start();
  void refresh();

  // Simulation-Specific functions
  virtual void step() = 0;
  virtual void render() = 0;
};
