#include "game.hpp"

Game::Game(int width, int height, char* window_title):
    m_width(width),
    m_height(height),
    m_window_title(window_title),
    m_quit(0)
{
}

Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::Update() {


    // TODO: move these concepts to their own class so each tile can hold
    // more data, like it's own coordinate, if it's passable, etc.
    // also have a map class which contains a vector<tile_t> tiles
    const int tile_w = 10;
    const int tile_h = 10;
    const int map_w = m_width / tile_w;
    const int map_h = m_height / tile_h;

    while(!m_quit) {
        SDL_PollEvent(&e);
        switch (e.type) {
            case SDL_QUIT: m_quit=1; break;
        }

        // rect_w and rect_h are actually maps width and height

        for(int y = 0; y < map_h; y++) {
            for(int x = 0; x < map_w; x++) {
                draw_rectangle(x*tile_w, y*tile_h, tile_w, tile_h, pack_color(x*3, 0, y*3, 255));

            }
        }

        SDL_RenderClear(renderer);
        // place m_framedata to the framebuffer
        SDL_UpdateTexture(framebuffer, NULL, static_cast<void*>(m_framedata.data()), m_width * 4);
        SDL_RenderCopy(renderer, framebuffer, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}

int Game::Init() {
    if(SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = NULL;
    renderer = NULL;

    if(SDL_CreateWindowAndRenderer(m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS, &window, &renderer)) {
        std::cerr << "Failed to initialize window, and renderer: " << SDL_GetError() << std::endl;
        return 1;
    }

    framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);

    if(!framebuffer) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return 1;
    }

    for (int i = 0; i < m_width*m_height; i++) {
        m_framedata.push_back(pack_color(0, 0, 0, 255));
    }
    

    SDL_SetWindowTitle(window, m_window_title);
    
    return 0;
}

uint32_t Game::pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {
    return (a<<24) + (b<<16) + (g<<8) + r;
}

void Game::draw_pixel(int x, int y, uint32_t color) {
    m_framedata[x + y*m_width] = color;
}

void Game::draw_rectangle(int x, int y, int w, int h, uint32_t color) {
    for (int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            if (x+i >= m_width || y+j >= m_height) continue;
            m_framedata[(x+i) + (y+j)*m_width] = color;
        }
    }
}