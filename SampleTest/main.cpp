#include <iostream>
#include <SDL2/SDL.h> 
#include <cmath>  // For sin, cos
#define SDL_MAIN_HANDLED
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
void logSDLError(std::ostream &os, const std::string &msg) {
    os << msg << " error: " << SDL_GetError() << std::endl;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        logSDLError(std::cerr, "SDL_Init");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Hello, SDL Graphics!",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          640, 480,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        logSDLError(std::cerr, "SDL_CreateWindow");
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        logSDLError(std::cerr, "SDL_CreateRenderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 100, 100, 200, 200);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    int center_x = 300;
    int center_y = 200;
    int radius = 50;
    for (int i = 0; i < 360; i++) {
        double angle = i * M_PI / 180.0;
        int x = center_x + (int)(radius * cos(angle));
        int y = center_y + (int)(radius * sin(angle));
        SDL_RenderDrawPoint(renderer, x, y);
    }
    std::cout << "Hello, Graphics! (See the window for drawing)" << std::endl;
    SDL_RenderPresent(renderer);
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) { 
                quit = true;
            }
        }
        SDL_Delay(10); 
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

