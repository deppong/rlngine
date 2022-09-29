#pragma once

#ifdef __unix__
    #include <SDL2/SDL.h>
#elif defined _WIN32
    #include "SDL.h"
#endif
#include <iostream>
#include <vector>
#include <stdlib.h>

class Game {
    public:
    // Constructor and Destructor
        Game(int width, int height, char* window_title);
        ~Game();
        void Update();
        int Init();

    private:
    // game state data
        int m_quit;
        char* m_window_title;

    // rendering data
        int m_width, m_height;
        SDL_Event e;
        SDL_Window*     window;
        SDL_Renderer*   renderer;
        SDL_Texture*    framebuffer;
        std::vector<uint32_t> framedata;

};