#ifndef GAME_HPP
#define GAME_HPP

#ifdef __unix__
    #include <SDL2/SDL.h>
#elif defined _WIN32
    #include "SDL.h"
#endif
#include "atlas.hpp"
#include "entity.hpp"

class Game {
    public:
    // Constructor and Destructor
        Game(int width, int height, char* window_title);
        ~Game();
        void Update();
        int Init();
    // rendering functions
        void draw_pixel(int x, int y, uint32_t color);
        void draw_rectangle(int x, int y, int w, int h, uint32_t color);
        void draw_sprite(std::vector<uint32_t> tex, int x, int y, int w);

    private:
    // game state data
        int m_quit;
        char* m_window_title;

    // rendering data
        int m_width, m_height;
        SDL_Event e;
        Atlas atlas;
        SDL_Window*     window;
        SDL_Renderer*   renderer;
        SDL_Texture*    framebuffer;
        std::vector<uint32_t> m_framedata;

};

#endif
