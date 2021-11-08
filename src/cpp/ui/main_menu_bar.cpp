#include "main_menu_bar.h"
#include "core.h"

#include "../main.h"
// using namespace ImGui;

void construct_menu_bar() {
    if (ImGui::BeginMainMenuBar()){

        if (ImGui::BeginMenu("File")) {
            ImGui::MenuItem("HELLO", NULL, false);
            if (APP_GLOBAL.vlc == NULL && ImGui::Button("Load VLC")) {
                init_vlc();
            }
            
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}