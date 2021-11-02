#include "../main.h"
#include "main_window.h"

namespace UI {

    void MainWindow::onDraw() {
        bool show = true;
        int w, h;
        SDL_GetWindowSize(APP_GLOBAL.window, &w, &h);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(w, h));
        ImGui::Begin("main_window", &show, BG_WINDOW_FLAGS);

        ImGui::End();
    }
}