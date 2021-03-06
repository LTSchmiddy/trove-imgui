#pragma once

#include <vector>
#include <vlc.hpp>

#include "ui/base/fragment.h"
#include "ui/main_window.h"
#include "ui/core.h"


struct AppGlobal {
    int target_fps = 60;
    std::vector<UI::Fragment*> fragments;
    SDL_Window* window;
    SDL_GLContext gl_context;
    VLC::Instance* vlc;
    bool show_demo_window = false;

    UI::MainWindow* main_window;
    UI::FWindow* style_window;
    UI::FWindow* py_console_window;

};

extern AppGlobal g_AppGlobal;

void init_vlc();
