#include "ui.hpp"

UI::UI(int width, int height) :
    m_atlas(16),
    m_width(width),
    m_height(height)
{

    if(m_atlas.load_atlas("../../res/Md_curses_16x16.png")) {
        std::cerr << "Failed to load texture" << std::endl;
    }
    for (int i = 0; i < m_width*m_height; i++) {
        framedata.push_back(COLOR_BLACK);
    }
};

UI::~UI() {
    SDL_DestroyTexture(framebuffer);
}

void UI::draw_sprite_color(std::vector<uint32_t> &texture, int x, int y, uint32_t color, uint32_t bg_color) {
    for (int i = 0; i < m_atlas.tex_width; i++) {
        for (int j = 0; j < m_atlas.tex_width; j++) {
            if(x+i >= m_width || y+j >= m_height || x+i <= 0 || y+j <= 0) continue;
            if (texture[i + j*m_atlas.tex_width] == COLORS[COLOR_WHITE]) {
                framedata[(x+i) + (y+j)*m_width] = color;
            } else {
                framedata[(x+i) + (y+j)*m_width] = bg_color;
            }
        }
    }
}

void UI::put_text(const std::string &text, int x, int y, uint32_t color, uint32_t bg_color) {
    ui_rect(x-1, y-1, text.length()+1, 2);
    int i = 0;
    for (char const &c : text) {
        draw_sprite_color(m_atlas.get_tile((int)c), (x + i) * m_atlas.tex_width, y * m_atlas.tex_width, color, bg_color);
        i++;
    }
}

void UI::ui_rect(int x, int y, int w, int h) {
    if (h < 1 || w < 1) {
        std::cout << "ui box must be at least a 1x1. be sure the all the parameters make sense for a line of text to fit inside" << std::endl;
        return;
    }

    int i=0, j=0;

    draw_sprite_color(m_atlas.get_tile(201), x * m_atlas.tex_width, y * m_atlas.tex_width, COLORS[COLOR_WHITE], COLORS[COLOR_BLACK]);

    for (i = 1; i < w; i++) {
        draw_sprite_color(m_atlas.get_tile(205), (x+i) * m_atlas.tex_width, y * m_atlas.tex_width, COLORS[COLOR_WHITE], COLORS[COLOR_BLACK]);
    }

    draw_sprite_color(m_atlas.get_tile(187), (x+i) * m_atlas.tex_width, y * m_atlas.tex_width, COLORS[COLOR_WHITE], COLORS[COLOR_BLACK] );

    for (j = 1; j < h; j++) {
        draw_sprite_color(m_atlas.get_tile(186), x * m_atlas.tex_width, (y+j) * m_atlas.tex_width, COLORS[COLOR_WHITE], COLORS[COLOR_BLACK]);
        for (i=1; i < w; i++) {
            draw_sprite_color(m_atlas.get_tile(' '), (x+i) * m_atlas.tex_width, (y+j) * m_atlas.tex_width, COLORS[COLOR_WHITE], COLORS[COLOR_BLACK]);
        }
        draw_sprite_color(m_atlas.get_tile(186), (x+i) * m_atlas.tex_width, (y+j) * m_atlas.tex_width, COLORS[COLOR_WHITE], COLORS[COLOR_BLACK]);

    }

    draw_sprite_color(m_atlas.get_tile(200), x * m_atlas.tex_width, (y+j) * m_atlas.tex_width, COLORS[COLOR_WHITE], COLORS[COLOR_BLACK]);

    for (i = 1; i < w; i++) {
        draw_sprite_color(m_atlas.get_tile(205), (x+i) * m_atlas.tex_width, (y+j) * m_atlas.tex_width, COLORS[COLOR_WHITE], COLORS[COLOR_BLACK]);
    }

    draw_sprite_color(m_atlas.get_tile(188), (x+i) * m_atlas.tex_width, (y+j) * m_atlas.tex_width, COLORS[COLOR_WHITE], COLORS[COLOR_BLACK]);

}