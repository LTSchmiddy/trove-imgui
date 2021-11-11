#include "main_menu_bar.h"
#include "core.h"

#include "../main.h"
// using namespace ImGui;

void construct_menu_bar() {
    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {
            
            ImGui::Checkbox("Show Demo Window", &g_AppGlobal.show_demo_window);
            ImGui::Checkbox("Show Style Window", &g_AppGlobal.style_window->open);
            ImGui::Checkbox("Show Python Console Window", &g_AppGlobal.py_console_window->open);
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}