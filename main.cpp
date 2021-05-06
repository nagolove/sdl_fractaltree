// SDL2 Hello, World!
// This should display a white screen for 2 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2

#include <numbers>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL_pixels.h>
#include <cmath>
#include <iostream>
#include <ostream>
#include <stdio.h>

//#define SCREEN_WIDTH 1920
//#define SCREEN_HEIGHT 1080

const uint SCREEN_WIDTH  = 1920;
const uint SCREEN_HEIGHT = 1080;

////const uint width  = 1920;
////const uint height = 1080;

double minLen = 10.;
#define PI 3.1415
//double angle = 26 * std::numbers::pi_v / 180
double angle = 26 * PI / 180;
//std::vector<SDL_Surface*> surfaces = {};
std::vector<SDL_Surface*> surfaces;
SDL_Renderer *renderer = nullptr;
Uint64 timeTick, lastTimeTick;

double lineLen = 127.;
double a_2 = SCREEN_WIDTH / 2, b_2 = SCREEN_HEIGHT - lineLen;
double a_ = 0.;
double b_ = 0.;

int mousex, mousey;

SDL_Surface* pushNewSurface(SDL_Surface* surf) {
    surfaces.push_back(surf);
    return surf;
}

void freeAllSurfaces() {
    for (uint32_t i = 0; i < surfaces.size(); ++i) {
        SDL_FreeSurface(surfaces[i]);
    }
}

const double magic = 0.f;

void rotate(double x, double y, double a, double *a_tmp, double *b_tmp) {
    double s = sin(a), c = cos(a);
    *a_tmp = x * c - y * s; *b_tmp = x * s + y * c;
}

Uint8 randColor() {
    // TODO напишите ваш код здесь
    return 1;
}

int branches(int deep, double a, double b, double len, double ang, double dir) {
    printf("deep %d, r %d, g %d, b %d, a %a\n");
    len = len * magic;

    if (len < minLen)
        return deep + 1;

    if (dir > 0) ang -= angle; else ang += angle;

    double vx = 0., vy = 0.;
    rotate(0, len, ang, &vx, &vy);

    vx = a + vx; vy = b - vy;
    //int succ = SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    Uint8 r_, g_, b_, a_;
    printf("color %d, %d, %d, %d\n", r_, g_, b_, a_);
    SDL_SetRenderDrawColor(renderer, r_, g_, b_, a_);

    branches(deep, vx, vy, len, ang, 1);
    branches(deep, vx, vy, len, ang, 0);
}

void fractaltree() {
    double a = a_2, b = b_2;
    int deep = 1;
    branches(deep, a, b, lineLen, a_, b_);
}

void present() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_Rect d = {0, 0, 800, 600};
    SDL_RenderFillRect(renderer, &d);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderDrawLine(renderer, 0, 0, d.w, d.h);
    SDL_RenderDrawLine(renderer, mousex-5, mousey-5, mousex+5, mousey+5);
    SDL_RenderDrawLine(renderer, mousex-5, mousey+5, mousex+5, mousey-5);

    //SDL_Color color = { .r = 255, .g = 255, .b = 255, .a = 255. };
    SDL_Color color = { .r = 25, .g = 0, .b = 0, .a = 0 };
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    fractaltree();

    SDL_RenderPresent(renderer);
}

void loop() {
    int last_ticks = SDL_GetTicks();
    bool quit = false;
    double px = 0., py = 0.;

    while (quit != true) {
        SDL_Event event;

        int next_ticks = SDL_GetTicks();
        std::cout << (1000 / (next_ticks - last_ticks + 1)) << "FPS" << std::endl;
        last_ticks = next_ticks;

        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_MOUSEMOTION:
                    px = event.motion.x;
                    py = event.motion.y;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_UP:
                            //specator.move_forwards(10);
                            break;
                        case SDLK_DOWN:
                            //specator.move_forwards(-10);
                            break;
                        case SDLK_LEFT:
                            //specator.move_sidewards(-10);
                            break;
                        case SDLK_RIGHT:
                            //specator.move_sidewards(10);
                            break;
                    }
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }

        if (event.type == SDL_MOUSEMOTION || 
                event.type == SDL_MOUSEBUTTONDOWN || 
                event.type == SDL_MOUSEBUTTONUP ||
                event.type == SDL_MOUSEWHEEL) {
            SDL_GetMouseState(&mousex, &mousey);
        }

        present();
    }
}

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow(
            "fractaltree",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
            );
    if (window == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer == NULL) {
        fprintf(stderr, "could'not create renderer %s\n", SDL_GetError());
    }

    int blackSurfaceW = 1024, blackSurfaceH = 768;
    //int pitch = 0; // 0 или 32 ??
    SDL_Surface *blackSurface = pushNewSurface(SDL_CreateRGBSurface(
                0, 
                blackSurfaceW,
                blackSurfaceH,
                32, 
                0, 0, 0, 0));
    SDL_FillRect(blackSurface, NULL, SDL_MapRGB(blackSurface->format, 0, 0, 0));

    screenSurface = SDL_GetWindowSurface(window);

    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    uint8_t r, g, b, a;
    int succ = SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    if (succ == -1) {
        fprintf(stderr, "SDL_GetRenderDrawColor() internal error %s\n", SDL_GetError());
    }
    printf("render color %d, %d, %d, %d\n", r, g, b, a);

    loop();

free_resources:

    freeAllSurfaces();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
//}
return 0;

}
