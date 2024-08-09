#pragma once

class MainMenuBar {
public:
    struct ViewControls {
        bool *sceneExplorerOpen, *assetExplorerOpen, *loggerOpen, *sceneEditorOpen;
    };

    ViewControls controls;
private:
public:
    MainMenuBar();
    ~MainMenuBar();

    void render();
};