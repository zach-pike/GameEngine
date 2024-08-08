#include "GameEngine.hpp"

#include <functional>

GameEngine::GameEngine() {}
GameEngine::~GameEngine() {}

void GameEngine::start() {
    renderThread = std::thread(std::bind(&GameEngine::runGame, this));
}

void GameEngine::join() {
    renderThread.join();
}