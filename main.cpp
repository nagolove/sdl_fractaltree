// SDL2 Hello, World!
// This should display a white screen for 2 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2
#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return 1;
    }
    window = SDL_CreateWindow(
            "hello_sdl2",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
            );
    if (window == NULL) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return 1;
    }

    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    printf("0\n");
    SDL_Delay(2000);
  //int last_ticks = SDL_GetTicks();
      bool quit = false;

    SDL_Event event;
    double px = 0, py = 0;

    printf("1\n");

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
                printf("quit\n");
                quit = true;
                break;
        }
    }

    printf("2\n");

    SDL_DestroyWindow(window);
    SDL_Quit();
    
//}
return 0;

}
