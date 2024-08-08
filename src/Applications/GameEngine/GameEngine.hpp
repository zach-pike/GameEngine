#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "App/App.hpp"

#include <thread>

class GameEngine : public App {
private:
    // Thread state do not modify pls thx
    GLFWwindow* window;

    std::thread renderThread;

    void init();
    void loop();
    void cleanup();

    void runGame();
public:
    GameEngine();
    ~GameEngine();

    void start();
    void join();
};