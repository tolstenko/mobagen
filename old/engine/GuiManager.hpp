#pragma once

#include <chrono>

#include "Window.hpp"
#include "Entity.hpp"

#include <imgui.h>

namespace mobagen {
  class GuiManager {
  public:
    GuiManager(const glm::vec2 &drawableSize, const glm::vec2 &displaySize, SDL_Window *sdlWindow);

    ~GuiManager(void);

    void render(Entity *sceneGraph);

    void tick(Window *window, std::chrono::microseconds delta);

    void addInputCharactersUTF8(const char *text);

    void setKeyEvent(int key, bool keydown);

    void togglePropertyEditor(void);

    void renderComponents(Entity *entity);

  private:
    void createDeviceObjects(void);

    void invalidateDeviceObjects(void);

    static void renderDrawLists(ImDrawData *draw_data);

    bool showProps;

    SDL_Window *m_sdlWindow;
  };
}