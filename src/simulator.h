#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <SDL2/SDL.h>
#include <vector>
#include "surface.h"

class Simulator {
    private:
        static const int WIN_WIDTH;
        static const int WIN_HEIGHT;
        static const SDL_Color hot_color;
        static const SDL_Color cold_color;
        SDL_Renderer* renderer;
        SDL_Window* window;
        SDL_Rect unit_rect;
        bool running, drawing;
        int unit_sz, x_dim, y_dim;
        Surface* plate;

        void temperature_to_rgb(double, SDL_Color&);
        void render();
        void update_state();
        void process_events();

    public:
        void run();
        Simulator(int);
        ~Simulator();
};

#endif
