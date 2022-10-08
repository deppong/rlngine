#include "game.hpp"

int main(int argc, char** argv) {
    Game game(800, 800, "RLNgine");
    if(game.Init()) {
        return 1;
    }

    game.Update();

    return 0;
}

