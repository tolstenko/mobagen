#pragma once

#include <chrono>

#include "GLManager.hpp"
#include "Window.hpp"
#include "GLEWManager.hpp"
#include "PhysicsManager.hpp"

#include "Game.hpp"

#include "Input.hpp"

namespace mobagen {
  class Engine {
  public:
    Engine(Game *game, char *windowTitle, glm::vec2 windowSize);

    ~Engine(void);

#ifdef EMSCRIPTEN
    static void loop(void);
#endif

    void tick(void);

    void start(void);

    Window *getWindow(void) const;

    GLManager *getGLManager(void) const;

    PhysicsManager *getPhysicsManager(void) const;

    std::chrono::microseconds getDeltaTime(void) const;

  private:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<GLEWManager> m_glewManager;
    std::unique_ptr<GLManager> m_glManager;
    std::unique_ptr<PhysicsManager> m_physicsManager;

    std::chrono::high_resolution_clock::time_point m_time, m_lastTime;
    std::chrono::duration<long long, std::micro> m_deltaTime;

    std::chrono::duration<long long, std::micro> m_physicsTimeAccumulated;
    std::chrono::duration<long long, std::micro> m_physicsTimeStepSize;

    std::chrono::duration<long long, std::micro> m_targetSleepTime;

    Game *game;

    bool quit, m_fireRay;
  };
}