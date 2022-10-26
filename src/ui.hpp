#pragma once
#ifndef UI_HPP
#define UI_HPP

#ifdef __unix__
    #include <SDL2/SDL.h>
#elif defined _WIN32
    #include "SDL.h"
#endif

#include "atlas.hpp"

class UI {
    public:
        UI();
        UI(int width, int height);
        ~UI();

        void put_text(const std::string &text, int x, int y, uint32_t color, uint32_t bg_color);
        void draw_sprite_color(std::vector<uint32_t> &tex, int x, int y, uint32_t color, uint32_t bg_color);
        void ui_rect(int x, int y, int w, int h);
        SDL_Texture* framebuffer;
        std::vector<uint32_t> framedata;
        int m_width, m_height;

    private:
        Atlas m_atlas;
};

#endif