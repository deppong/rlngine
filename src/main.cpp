#ifdef __unix__
    #include <SDL2/SDL.h>
#elif defined _WIN32
    #include <SDL.h>
#endif

#include <iostream>
#include <stdlib.h>


const int WIDTH = 800, HEIGHT = 800;

int main(void) {

    int quit = 1;

    SDL_Event e;
    if(SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if(SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS, &window, &renderer)) {
        std::cerr << "Failed to initialize window: " << SDL_GetError() << std::endl;
        return -1;
    }


    while(quit) {
        SDL_PollEvent(&e);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        switch (e.type) {
            case SDL_QUIT: quit=0; break;
        }


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
