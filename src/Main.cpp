#include "Applications/GameEngine/GameEngine.hpp"

int main() {
    auto game = std::make_unique<GameEngine>();
    game->start();
    game->join();

    return 0;
}