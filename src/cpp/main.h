#include <vector>

#include "ui/core.h"
#include "ui/base/fragment.h"

struct AppGlobal {
    int target_fps = 60;
    std::vector<UI::Fragment*> fragments;
    SDL_Window* window;
    bool show_demo_window = false;

};

extern AppGlobal APP_GLOBAL;