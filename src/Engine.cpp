//
// Created by matteo on 11/4/21.
//
#include "Engine.hpp"

#define UPDATE_STEPS 60

Engine::Engine(int w, int h) : WIDTH(w), HEIGHT(h) {
  open = running = false;
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
  screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
}

Engine::~Engine() = default;

void Engine::start() {
  unsigned n_updates = 0;
  open = true;
  while (open) {
    process_events();
    // Just render the current state if the application is actually running
    if (running) {
      if(n_updates == UPDATE_STEPS) {
        render();
        refresh();
        // Here we sleep 60ms no matter what, it is possible to take a more intelligent approach
        SDL_Delay(60);
        n_updates = 0;
      }
      step();
      n_updates += 1;
    } else {
      render();
      refresh();
    }
  }
}

void Engine::refresh() {
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, screen, nullptr, nullptr);
  SDL_RenderPresent(renderer);
}

void Engine::process_events() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
        handle_key(event.key.keysym.sym);
        break;
      case SDL_QUIT:
        open = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        drawing = true;
        break;
      case SDL_MOUSEBUTTONUP:
        drawing = false;
        break;
    }
  }
  if(drawing) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    click(x, y);
  }
}

void Engine::handle_key(SDL_Keycode code) {
  switch (code) {
    case SDLK_ESCAPE:
      open = false;
      break;
    case SDLK_SPACE:
      running = !running;
      break;
  }
}