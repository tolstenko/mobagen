#include "Engine.hpp"
#include "Logger.hpp"
#include "Ray.hpp"
#include "GuiManager.hpp"
#include "ForwardRenderer.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <chrono>

#include <limits>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#if defined(__MINGW32__) || defined(_MSC_VER)
#include <thread>
#endif

using namespace std::chrono_literals;

namespace mobagen {
#ifdef EMSCRIPTEN
  static Engine *instance = NULL;
#endif

  Engine::Engine(Game *game, char *windowTitle, glm::vec2 windowSize) {
    log_info("Initializing SDL");
    m_window = std::make_unique<Window>(windowTitle, windowSize);

    log_info("Initializing GLEW");
    m_glewManager = std::make_unique<GLEWManager>();

    log_info("Initializing GL");
    m_glManager = std::make_unique<GLManager>(std::make_unique<ForwardRenderer>(), m_window->getDrawableSize());

    log_info("Initializing Physics Manager");
    m_physicsManager = std::make_unique<PhysicsManager>();

    this->game = game;

    quit = false;
    m_fireRay = false;

    m_targetSleepTime = std::chrono::duration<long long, std::micro>(1000000/60);
  }

  Engine::~Engine(void) {
  }

  void Engine::start(void) {
    game->setEngine(this);

    game->getRootScene()->registerWithEngineAll(this);

    log_info("Initializing game");

    m_window->init();

    game->init(m_glManager.get());

    m_window->makeCurrentContext();

    m_window->getInput()->registerKeyToAction(SDLK_F1, "propertyEditor");
    m_window->getInput()->registerKeyToAction(SDLK_F2, "fullscreenToggle");

    m_window->getInput()->registerButtonToAction(SDL_BUTTON_LEFT, "fireRay");

    m_window->getInput()->bindAction("propertyEditor", IE_PRESSED, [this]() {
      m_window->getGuiManager()->togglePropertyEditor();
    });

    m_window->getInput()->bindAction("fullscreenToggle", IE_PRESSED, [this]() {
      m_window->toggleFullscreen();
      m_glManager->setDrawSize(m_window->getDrawableSize());
    });

    m_window->getInput()->bindAction("fireRay", IE_PRESSED, [this]() {
      m_fireRay = true;
    });

    m_window->getInput()->bindAction("fireRay", IE_RELEASED, [this]() {
      m_fireRay = false;
    });

    m_time = std::chrono::high_resolution_clock::now();

    m_physicsTimeStepSize = std::chrono::microseconds(1000000/360); // 6 steps per frame
    m_physicsTimeAccumulated = std::chrono::microseconds(0);

#ifdef EMSCRIPTEN
    instance = this;
    emscripten_set_main_loop(Engine::loop, 0, 1);
#else
    auto preTick = std::chrono::high_resolution_clock::now();
    auto m_sleepError = std::chrono::microseconds(0);
    while (!quit) {
      tick();
      auto posTick = std::chrono::high_resolution_clock::now();
      auto tickTime = std::chrono::duration_cast<std::chrono::microseconds>(posTick - preTick);
      auto sleepTime = std::chrono::duration_cast<std::chrono::microseconds>(m_targetSleepTime - tickTime - m_sleepError);

      if(sleepTime<std::chrono::microseconds::zero()) sleepTime = std::chrono::microseconds::zero();
#if defined(__MINGW32__) || defined(_MSC_VER)
      std::this_thread::sleep_for(sleepTime);
#else
      SDL_Delay((uint32_t)(sleepTime.count()/1000));
#endif

      auto posSleep = std::chrono::high_resolution_clock::now();
      m_sleepError = std::chrono::duration_cast<std::chrono::microseconds>(posSleep-posTick) - sleepTime;
      preTick = posSleep;
    }
#endif
  }

#ifdef EMSCRIPTEN
  void Engine::loop(void)
  {
    instance->tick();
  }
#endif

  void Engine::tick(void) {
    m_lastTime = m_time;
    m_time = std::chrono::high_resolution_clock::now();
    m_deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(m_time - m_lastTime);

    m_window.get()->tick();
    m_window.get()->getGuiManager()->tick(m_window.get(), m_deltaTime);

    quit = m_window.get()->shouldQuit();

    // Fixed timestep
    m_physicsTimeAccumulated += m_deltaTime; // get the remaining from the last step
    while (m_physicsTimeAccumulated >= m_physicsTimeStepSize) {
      m_physicsTimeAccumulated -= m_physicsTimeStepSize;
      m_physicsManager.get()->tick(m_physicsTimeStepSize);
    }
    // TODO: we need to simulate the remaining time and render it in order to avoid jitter on the last simulation step

    game->update(m_window->getInput(), m_deltaTime);

    game->render(m_glManager.get());

    m_window->getGuiManager()->render(game->getRootScene().get());

    m_window->swapBuffer();
  }

  Window *Engine::getWindow(void) const {
    return m_window.get();
  }

  GLManager *Engine::getGLManager(void) const {
    return m_glManager.get();
  }

  PhysicsManager *Engine::getPhysicsManager(void) const {
    return m_physicsManager.get();
  }

  std::chrono::microseconds Engine::getDeltaTime(void) const {
    return m_deltaTime;
  }

}