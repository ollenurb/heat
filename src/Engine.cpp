//
// Created by matteo on 11/4/21.
//
#include "Engine.hpp"
#include <iostream>

#define UPDATE_STEPS 20

Engine::Engine(int w, int h) : WIDTH(w), HEIGHT(h) {
  running = false;
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
  screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
}

Engine::~Engine() = default;

void Engine::run() {
  unsigned n_frame = 0;
  unsigned long long iterations = 0;
  running = true;
  while (running) {
    process_events();
    /* TODO: Change 10 with AFTER_NFRAMES */
    if (n_frame == UPDATE_STEPS) {
      render();
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, screen, nullptr, nullptr);
      SDL_RenderPresent(renderer);
      n_frame = 0;
      SDL_Delay(60);
      iterations++;
    }
    step();
    n_frame++;
  }
  std::cout << "Simulations took " << iterations << " iterations" << std::endl;
}

void Engine::process_events() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          running = false;
        }
        break;
      case SDL_QUIT:
        running = false;
        break;
    }
  }
}