#pragma once

#include "ui/core.h"
#include "ui/base/fragment.h"
#include "python/py_main.h"

namespace UI {
ImGuiInputTextCallback text_callback(ImGuiInputTextCallbackData data);

class PyConsole : public Fragment {
public:
    std::string input_text;

    // void onBackground() override;
    // bool onEvent(SDL_Event* event) override;
    void onDraw() override;

    
};
}