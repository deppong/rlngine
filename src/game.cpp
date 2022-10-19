#include "game.hpp"

Game::Game(int width, int height, char* window_title):
    m_width(width),
    m_height(height),
    m_window_title(window_title),
    m_quit(0),
    atlas(16),
    world(width, height, 16)
{
}

Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(framebuffer);
    SDL_Quit();
}

int Game::Init() {
    if(SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = NULL;
    renderer = NULL;

    if(SDL_CreateWindowAndRenderer(m_width, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        std::cerr << "Failed to initialize window, and renderer: " << SDL_GetError() << std::endl;
        return 1;
    }

    framebuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);
    SDL_SetTextureBlendMode(framebuffer, SDL_BLENDMODE_NONE);

    if(!framebuffer) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return 1;
    }

    for (int i = 0; i < m_width*m_height; i++) {
        m_framedata.push_back(COLOR_BLACK);
    }
    

    SDL_SetWindowTitle(window, m_window_title);

    if(atlas.load_atlas("../../res/Md_curses_16x16.png")) {
        std::cerr << "Failed to load texture" << std::endl;
        return 1;
    }
    

    return 0;
}

void Game::Update() {

    // random number initialization 
    std::random_device rd;
    std::mt19937 gen(rd());

    auto player = world.factory.add_object("player", world.zones[4].m_registry);
    // auto snake = world.factory.add_object("snake", world.zones[4].m_registry);

    // should just construct zones as we enter them
    for (int i = 0; i < 9; i++) {
        world.construct_zone(i);
    }

    // ai random movement range distribution
    std::uniform_int_distribution<> distr(-1, 1);


    // main update loop
    while(!m_quit) {

        // clear framebuffer
        for (size_t i = 0; i < m_width * m_height; i++) {
            m_framedata[i] = COLOR_BLACK;
        }

        // events
        SDL_WaitEvent(&e);
        switch (e.type) {
            case SDL_QUIT: m_quit=1; break;

            // This needs to be decoupled from the actual sdl events
            case SDL_KEYDOWN:
                auto group = world.zones[world.current_zone].m_registry.group<ControllableComponent>(entt::get<PhysicsComponent>);
                for (auto entity : group) {
                    auto [control, physics] = group.get<ControllableComponent, PhysicsComponent>(entity);
                    if (control.inControl) {
                        switch (e.key.keysym.sym) {
                            case SDLK_h: physics.vel_x = -1; break;
                            case SDLK_j: physics.vel_y =  1; break;
                            case SDLK_k: physics.vel_y = -1; break;
                            case SDLK_l: physics.vel_x =  1; break;
                            case SDLK_y: physics.vel_x = -1; physics.vel_y = -1; break;
                            case SDLK_u: physics.vel_x =  1; physics.vel_y = -1; break;
                            case SDLK_b: physics.vel_x = -1; physics.vel_y =  1; break;
                            case SDLK_n: physics.vel_x =  1; physics.vel_y =  1; break;
                            case SDLK_PERIOD: break; // wait command, wait one turn
                            case SDLK_2: 
                                world.current_zone = 2;
                                std::cout << world.current_zone << std::endl;
                                break;
                            case SDLK_4: 
                                world.current_zone = 4;
                                std::cout << world.current_zone << std::endl;
                                break;

                        }

                    }
                }
                world.new_turn = true;
            break;
        }

        if (world.new_turn) {
            // Placeholder for ai 
            // auto &physics = world.zones[world.current_zone].m_registry.get<PhysicsComponent>(snake);
            // physics.vel_x = distr(gen);
            // physics.vel_y = distr(gen);

            world.update_physics();

            world.new_turn = false;
        }

        // render loop
        auto group = world.zones[world.current_zone].m_registry.group<RenderComponent, TransformComponent>();
        for (auto entity : group) {

            auto [transform, tile] = group.get<TransformComponent, RenderComponent>(entity);


            draw_sprite_color(atlas.get_tile(tile.tile), transform.x * atlas.tex_width, transform.y * atlas.tex_width, COLORS[tile.color], COLORS[tile.bg_color]);
        }

        SDL_RenderClear(renderer);
        // place m_framedata to the framebuffer
        SDL_UpdateTexture(framebuffer, NULL, static_cast<void*>(m_framedata.data()), m_width * 4);
        SDL_RenderCopy(renderer, framebuffer, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}


// --------------------------
// Rendering helper functions

void Game::draw_pixel(int x, int y, uint32_t color) {
    m_framedata[x + y*m_width] = color;
}

void Game::draw_rectangle(int x, int y, int w, int h, uint32_t color) {
    for (int i = 0; i < w; i++) {
        for(int j = 0; j < h; j++) {
            if (x+i >= m_width || y+j >= m_height) continue;
            if(x+i <= 0 || y+j <= 0) continue;
            m_framedata[(x+i) + (y+j)*m_width] = color;
        }
    }
}

// This seems redundant to the above function, and it is!
// instead of some constant color, you just pull the color from whatever the 
// texture had
void Game::draw_sprite(std::vector<uint32_t> &texture, int x, int y, int w) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < w; j++) {
            if(x+i >= m_width || y+j >= m_height) continue;
            if(x+i <= 0 || y+j <= 0) continue;
            m_framedata[(x+i) + (y+j)*m_width] = texture[i + j*w];
        }
    }
}

void Game::draw_sprite_color(std::vector<uint32_t> &texture, int x, int y, uint32_t color, uint32_t bg_color) {
    for (int i = 0; i < atlas.tex_width; i++) {
        for (int j = 0; j < atlas.tex_width; j++) {
            if(x+i >= m_width || y+j >= m_height || x+i <= 0 || y+j <= 0) continue;
            if (texture[i + j*atlas.tex_width] == COLORS[COLOR_WHITE]) {
                m_framedata[(x+i) + (y+j)*m_width] = color;
            } else {
                m_framedata[(x+i) + (y+j)*m_width] = bg_color;
            }
        }
    }
}
