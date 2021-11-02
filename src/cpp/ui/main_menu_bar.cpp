
#include "core.h"
// using namespace ImGui;

void construct_menu_bar() {
    if (ImGui::BeginMainMenuBar()){

        if (ImGui::BeginMenu("File")) {
            ImGui::MenuItem("HELLO", NULL, false);
            
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}