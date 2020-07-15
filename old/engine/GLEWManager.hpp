#pragma once

namespace mobagen {
  class GLEWManager {
  public:
    GLEWManager(void);

    ~GLEWManager(void);

    void clean(void);

    int init(void);

  private:
  };
}