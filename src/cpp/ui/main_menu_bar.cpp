#include "main_menu_bar.h"
#include "core.h"

#include "../main.h"
// using namespace ImGui;

void construct_menu_bar() {
    if (ImGui::BeginMainMenuBar()) {

        if (ImGui::BeginMenu("File")) {
            
            ImGui::Checkbox("Show Demo Window", &APP_GLOBAL.show_demo_window);
            ImGui::Checkbox("Show Style Window", &APP_GLOBAL.show_style_window);
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}