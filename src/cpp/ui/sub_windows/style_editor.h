#pragma once

#include "ui/core.h"
#include "ui/base/fragment.h"
#include "python/py_main.h"

namespace UI {
    py::dict style_save_dict(ImGuiStyle* s);
    void style_load_dict(ImGuiStyle* s, py::dict d);
    void save_style();
    void load_style();
    void draw_style_window(bool* show_window);

    class StyleEditor : public Fragment {
        void onDraw() override;
    };
}