#include "GameEngine.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "Utility/GL/ShaderProgram/ShaderProgram.hpp"
#include "Utility/GL/VertexArray/VertexArray.hpp"
#include "Utility/GL/Buffer/Buffer.hpp"
#include "Utility/GL/Texture/Texture.hpp"

#include "MyUtility/CameraControllers/FreecamController/FreecamController.hpp"
#include "MyUtility/CameraControllers/FreecamController/CameraProgram/CameraProgram.hpp"

#include "MyUtility/ShaderLoaders/VertexFragment/VertexFragment.hpp"

#include "ImGui/AssetExplorer/AssetExplorer.hpp"
#include "ImGui/MainMenuBar/MainMenuBar.hpp"
#include "ImGui/SceneExplorer/SceneExplorer.hpp"
#include "ImGui/LoggerWindow/LoggerWindow.hpp"

#include "SceneEditor/SceneEditor.hpp"
#include "Scene/Scene.hpp"

#include <stb_image.h>

#include <iostream>
#include <exception>
#include <functional>

void GameEngine::init() {
    if (!glfwInit()) {
        std::cout << "Failed to init GLFW!\n";
        std::exit(1);
    }

    window = glfwCreateWindow(1200, 800, "Game Engine", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to load OpenGL/GLAD!\n";
        std::exit(1);
    }

    GLFWimage images[1]; 
    images[0].pixels = stbi_load("resources/icon.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
    glfwSetWindowIcon(window, 1, images); 
    stbi_image_free(images[0].pixels);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    const char* vendor = (char*)glGetString(GL_VENDOR); // Returns the vendor
    const char* renderer = (char*)glGetString(GL_RENDERER); // Returns a hint to the model

    printf("Vendor: %s\nRenderer: %s\n", vendor, renderer);
}

void GameEngine::loop() {
    // VAO
    VertexArray vao;
    vao.bindVertexArray();
    
    std::shared_ptr<LoggerWindow> logger = std::make_shared<LoggerWindow>();

    LoggerProfile myProfile(logger, "MyLogger");
    myProfile.logInfo("AAAAAh");
    myProfile.logInfo("AAAAAh");
    myProfile.logInfo("AAAAAh");
    myProfile.logInfo("AAAAAh");

    AssetExplorer assetExplorer;

    std::shared_ptr<Shape> selectedObject;
    SceneExplorer sceneExplorer;
    SceneEditor   sceneEditor;

    MainMenuBar   mainMenuBar;
    mainMenuBar.controls.assetExplorerOpen = &assetExplorer.open;
    mainMenuBar.controls.sceneExplorerOpen = &sceneExplorer.open;
    mainMenuBar.controls.loggerOpen        = &logger->open;
    mainMenuBar.controls.sceneEditorOpen   = &sceneEditor.open;

    auto scene = std::make_shared<Scene>("My Scene");

    sceneExplorer.setScene(scene);
    sceneEditor.setScene(scene);

    double lastFrameStartTime = glfwGetTime();
    float aspectRatio;
    while(!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) {
        double frameStartTime = glfwGetTime();

        // DeltaT calc
        double deltaTime = frameStartTime - lastFrameStartTime;
    
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        if (windowWidth != 0 && windowHeight != 0) {
            aspectRatio = (float)windowWidth / (float)windowHeight;
        }

        // Drawing code
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Dockspace
        ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

        ImGuiWindowFlags extraFlags = sceneEditor.getCameraController().isMouseLocked ? ImGuiWindowFlags_NoInputs : 0;

        // // Draw my game engine windows
        // mainMenuBar.render();

        assetExplorer.render(extraFlags);
        sceneExplorer.render(extraFlags, selectedObject);
        logger->render(extraFlags);

        sceneEditor.render(extraFlags, window, deltaTime, selectedObject);
        
        ImGui::ShowDemoWindow();
        
        // Render ImGui stuff
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, windowWidth, windowHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Frame limiter
        const double frameEndTime = glfwGetTime();
        const double frameTimeMS = (frameEndTime - frameStartTime) * 1e6;
        const double requiredFrameTimeMS = 8333.33;
        const double sleepTime = requiredFrameTimeMS - frameTimeMS;

        if (sleepTime > 0) std::this_thread::sleep_for(std::chrono::microseconds((std::int64_t)sleepTime));

        // Update dt calculation
        lastFrameStartTime = frameStartTime;

        glfwSwapBuffers(window);
        
        // Make viewport always the same size as window
        glViewport(0, 0, windowWidth, windowHeight);
    } 
}

void GameEngine::cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

void GameEngine::runGame() {
    init();
    loop();
    cleanup();
}