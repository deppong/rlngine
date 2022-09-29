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

    int r=0, g=0, b=0;

    while(!m_quit) {
        SDL_PollEvent(&e);
        switch (e.type) {
            case SDL_QUIT: m_quit=1; break;
        }

        // changing data in the framebuffer making sure it is running properly
        r++;
        g++;


        // edit render methods here 
        for (int i = 0; i < m_width*m_height; i++) {
            // TODO: add utility function to properly pack the color
            framedata[i] = ((255<<24) + (b<<16) + (g<<8) + r);
        }


        SDL_RenderClear(renderer);
        // place framedata to the framebuffer
        SDL_UpdateTexture(framebuffer, NULL, static_cast<void*>(framedata.data()), m_width * 4);
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
        // TODO: add utility function to properly pack the color
        framedata.push_back((255<<24) + (100<<16) + (0<<8) + 0);
    }
    

    SDL_SetWindowTitle(window, m_window_title);
    
    return 0;
}