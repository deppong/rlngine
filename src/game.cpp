#include "game.hpp"

Game::Game(int width, int height, char* window_title):
    m_width(width),
    m_height(height),
    m_window_title(window_title),
    m_quit(1)
{
}

Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::Update() {

    while(m_quit) {
        SDL_PollEvent(&e);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        switch (e.type) {
            case SDL_QUIT: m_quit=0; break;
        }


        SDL_RenderPresent(renderer);
    }
}

int Game::Init() {
    if(SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 0;
    }

    window = NULL;
    renderer = NULL;

    if(SDL_CreateWindowAndRenderer(m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS, &window, &renderer)) {
        std::cerr << "Failed to initialize window, and renderer: " << SDL_GetError() << std::endl;
        return 0;
    }

    framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);

    if(!framebuffer) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return 0;
    }

    SDL_SetWindowTitle(window, m_window_title);
    
    return 1;
}