#include "game.hpp"

Game::Game(int width, int height, char* window_title):
    m_width(width),
    m_height(height),
    m_window_title(window_title),
    m_quit(0),
    atlas(10)
{
}

Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::Update() {
    srand(time(0));

    const int map_w = m_width / atlas.tex_width;
    const int map_h = m_height / atlas.tex_width;


    // main update loop
    while(!m_quit) {
        SDL_PollEvent(&e);
        switch (e.type) {
            case SDL_QUIT: m_quit=1; break;
        }

        // draw_sprite(atlas.get_texture(randx, randy), i*10, j*10, atlas.tex_width);
        draw_sprite(atlas.from_char('T'), 0*10, 0*10, atlas.tex_width);
        draw_sprite(atlas.from_char('e'), 1*10, 0*10, atlas.tex_width);
        draw_sprite(atlas.from_char('s'), 2*10, 0*10, atlas.tex_width);
        draw_sprite(atlas.from_char('t'), 3*10, 0*10, atlas.tex_width);
        draw_sprite(atlas.from_char(0x2320), 4*10, 0*10, atlas.tex_width);
        draw_sprite(atlas.from_char(0x2321), 4*10, 1*10, atlas.tex_width);


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

    if(atlas.load_texture("../../res/cp437_10x10.png")) {
        std::cerr << "Failed to load texture" << std::endl;
        return 1;
    }
    
    return 0;
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

// This seems redundant to the above function, and it is!
// instead of some constant color, you just pull the color from whatever the 
// texture had
void Game::draw_sprite(std::vector<uint32_t> texture, int x, int y, int w) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < w; j++) {
            if(x+i >= m_width || y+j >= m_height) continue;
            m_framedata[(x+i) + (y+j)*m_width] = texture[i + j*w];
        }
    }
}