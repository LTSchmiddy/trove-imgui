#pragma once

#include <vector>
#include <vlc.hpp>

#include "ui/base/fragment.h"
#include "ui/core.h"

struct AppGlobal {
    int target_fps = 60;
    std::vector<UI::Fragment*> fragments;
    SDL_Window* window;
    SDL_GLContext gl_context;
    VLC::Instance* vlc;
    bool show_demo_window = false;
    bool show_style_window = false;
};

extern AppGlobal APP_GLOBAL;

void init_vlc();
