#pragma once
#include "containers/types.hpp"
#include "../Time.hpp"
#include "IUpdatable.hpp"

class GameLoop {
private:
  u64 t=0;
  u64 dt=0;

  u64 currentTime = Time::MicroSecSinceMachineStart();
  u64 accumulated = 0;
  
  IUpdatable updatable;

public:
  explicit GameLoop(IUpdatable updatable, u16 fps=60);
  
  void Start();
  void Pause();
  void Continue();
  void Stop();

private:
  void Run();
};

