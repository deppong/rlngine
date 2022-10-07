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
    SDL_Quit();
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

    if(atlas.load_atlas("../../res/Md_curses_16x16.png")) {
        std::cerr << "Failed to load texture" << std::endl;
        return 1;
    }

    srand(time(0));

    return 0;
}

void Game::Update() {


    entt::entity player = world.m_registry.create();
    world.m_registry.emplace<TransformComponent>(player, 40, 40);
    world.m_registry.emplace<RenderComponent>(player, '@', COLOR_WHITE, COLOR_BLACK);
    world.m_registry.emplace<PhysicsComponent>(player, 0, 0);
    world.m_registry.emplace<ControllableComponent>(player, true);

    entt::entity goblin = world.m_registry.create();
    world.m_registry.emplace<TransformComponent>(goblin, 3, 3);
    world.m_registry.emplace<RenderComponent>(goblin, 'g', COLOR_LIME, COLOR_BLACK);
    world.m_registry.emplace<PhysicsComponent>(goblin, 0, 0);
    world.m_registry.emplace<ControllableComponent>(goblin, false);

    entt::entity kobold = world.m_registry.create();
    world.m_registry.emplace<TransformComponent>(kobold, 4, 4);
    world.m_registry.emplace<RenderComponent>(kobold, 'k', COLOR_FUCHSIA, COLOR_BLACK);
    world.m_registry.emplace<PhysicsComponent>(kobold, 0, 0);

    // main update loop
    while(!m_quit) {
        // clear frambuffer
        for (size_t i = 0; i < m_width * m_height; i++) {
            m_framedata[i] = COLOR_BLACK;
        }

        // events
        SDL_PollEvent(&e);
        switch (e.type) {
            case SDL_QUIT: m_quit=1; break;

            case SDL_KEYDOWN:
                auto group = world.m_registry.group<ControllableComponent>(entt::get<PhysicsComponent>);
                for (auto entity : group) {
                    auto& [control, physics] = group.get<ControllableComponent, PhysicsComponent>(entity);
                    if (control.inControl) {
                        switch (e.key.keysym.sym) {
                            case SDLK_h: physics.vel_x = -1; break;
                            case SDLK_j: physics.vel_y =  1; break;
                            case SDLK_k: physics.vel_y = -1; break;
                            case SDLK_l: physics.vel_x =  1; break;
                        }

                    }
                }
            break;
        }

        // physics loop
        auto group = world.m_registry.group<TransformComponent>(entt::get<PhysicsComponent>);
        for (auto entity : group) {
            auto&[transform, physics] = group.get<TransformComponent, PhysicsComponent>(entity);

            transform.x += physics.vel_x;
            transform.y += physics.vel_y;

            physics.vel_x = 0;
            physics.vel_y = 0;
        }

        // render loop
        auto view = world.m_registry.view<TransformComponent, RenderComponent>();
        for (auto entity : view) {

            auto&[transform, tile] = view.get<TransformComponent, RenderComponent>(entity);

            draw_sprite(atlas.set_color(atlas.get_tile(tile.tile), tile.color, tile.bg_color), transform.x * atlas.tex_width, transform.y * atlas.tex_width, atlas.tex_width);
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