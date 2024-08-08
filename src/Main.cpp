#include "Applications/MyApp/MyApp.hpp"

int main() {
    auto game = std::make_unique<MyApp>();
    game->start();
    game->join();

    return 0;
}