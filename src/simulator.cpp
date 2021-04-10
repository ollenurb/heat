#include "simulator.h"
#include "surface.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include <algorithm>

/* Maximum and minimum temperatures reachable */
#define MAX_TEMP 150
#define MIN_TEMP -20

using namespace std;

const int Simulator::WIN_WIDTH = 960;
const int Simulator::WIN_HEIGHT = 640;
const string WIN_TITLE = "Heat Equation";

/* Colors used to represent hot and cold temperatures */
const SDL_Color Simulator::hot_color = {3, 157, 252, SDL_ALPHA_OPAQUE};
const SDL_Color Simulator::cold_color = {252, 94, 3, SDL_ALPHA_OPAQUE};

/*
 * Constructor takes the size of a pixel. If either win_height or win_width are
 * not divisible by this value, an exception is thrown.
 */
Simulator::Simulator(int unit_sz)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) cerr << "Error while initializing SDL: " << SDL_GetError() << endl;
    if(SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, 0, &window, &renderer) < 0) cerr << "Error while initializing window and renderer" << SDL_GetError() << endl;
    SDL_SetWindowTitle(window, WIN_TITLE.c_str());
    running = false;
    drawing = false;
    this->unit_sz = unit_sz;

    if(WIN_WIDTH % unit_sz != 0 || WIN_HEIGHT % unit_sz != 0) {
        throw invalid_argument("Pixel size is not divisible for either window height or width");
    }

    x_dim = WIN_WIDTH / unit_sz;
    y_dim = WIN_HEIGHT / unit_sz;

    plate = new Surface(x_dim, y_dim, 1.0);
    plate->init(0);
}

Simulator::~Simulator()
{
    delete plate;
}

/*
 * Render a single frame of the simulation
 */
void Simulator::render()
{
    double val;
    unit_rect.x = 0;
    unit_rect.y = 0;
    unit_rect.w = unit_rect.h = unit_sz;
    SDL_Color color;
    color.a = SDL_ALPHA_OPAQUE;

    for(int i = 0; i <= y_dim; i++) {
        unit_rect.y = unit_sz * i;
        for(int j = 0; j <= x_dim; j++) {
            unit_rect.x = unit_sz * j;
            val = plate->getrc(i + 1, j + 1);
            temperature_to_rgb(val, color);
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &unit_rect);
        }
    }
    SDL_RenderPresent(renderer);
}

/*
 * Compute a step in time in the simulation
 */
void Simulator::update_state()
{
    plate->compute_step();
}

/*
 * Convert a given temperature value into an actual RGB color.
 */
void Simulator::temperature_to_rgb(double temp, SDL_Color& color)
{
    double norm_temp = (temp - MIN_TEMP / (MAX_TEMP - MIN_TEMP));
    double r_val = (double) (cold_color.r - hot_color.r) * norm_temp + hot_color.r;
    double g_val = (double) (cold_color.g - hot_color.g) * norm_temp + hot_color.g;
    double b_val = (double) (cold_color.b - hot_color.b) * norm_temp + hot_color.b;

    color.r = std::clamp<double>(r_val, 0, 255);
    color.g = std::clamp<double>(g_val, 0, 255);
    color.b = std::clamp<double>(b_val, 0, 255);
}

/*
 * Handle mouse click and window closed events
 */
void Simulator::process_events()
{
    SDL_Event event;

    int x, y;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                drawing = true;
                break;

            case SDL_MOUSEBUTTONUP:
                drawing = false;
                break;
        }
    }

    /* Handle apply heat with mouse */
    if(drawing) {
        SDL_GetMouseState(&x, &y);
        x = (x/unit_sz)+1;
        y = (y/unit_sz)+1;
        plate->getrc(y, x) += 10;
    }
}

/*
 * Start the simulation
 */
void Simulator::run()
{
    running = true;
    while(running) {
        process_events();
        update_state();
        render();
        SDL_Delay(60);
    }
}
