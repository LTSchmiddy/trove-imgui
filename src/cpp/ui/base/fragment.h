#pragma once

#include "../core.h"
#include <imgui.h>
#include <string>

namespace UI {
const ImGuiWindowFlags BG_WINDOW_FLAGS = 0
    | ImGuiWindowFlags_NoResize
    | ImGuiWindowFlags_NoCollapse
    | ImGuiWindowFlags_NoBringToFrontOnFocus
    | ImGuiWindowFlags_UnsavedDocument
    | ImGuiWindowFlags_NoMove
    // | ImGuiWindowFlags_NoTitleBar
    ;

class Fragment {

public:
    // Generally, Fragments shouldn't not be stored on the stack.
    // But, if you must, set this flag that the cleanup process knows to ignore them.
    bool delete_during_cleanup = true;

    bool should_draw = true;

    virtual bool onEvent(SDL_Event* event);
    virtual void onBackground();
    virtual void onDraw();
};

class FWindow : public Fragment {
public:
    std::string id;
    bool open = true;
    ImGuiWindowFlags flags = 0;
    Fragment* content;

    bool destruct_content = false;

    FWindow(std::string p_id, Fragment* p_content, bool p_destruct_content = false, bool p_start_open = true, ImGuiWindowFlags p_flags = 0);
    ~FWindow();

    bool onEvent(SDL_Event* event) override;
    void onBackground() override;
    void onDraw() override;
};
}
