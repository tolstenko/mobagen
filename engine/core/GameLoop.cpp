#include "GameLoop.hpp"

GameLoop::GameLoop(IUpdatable updatable, u16 fps) {
  dt = 1.0/fps;
  this->updatable = updatable;
}

void GameLoop::Start() {

}

void GameLoop::Pause() {

}

void GameLoop::Continue() {

}

void GameLoop::Stop() {

}

void GameLoop::Run() {

}
