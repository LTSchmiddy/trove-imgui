#include "main_window.h"
#include "../main.h"

// #include <vlc.hpp>

namespace UI {
MainWindow::MainWindow() {
    movie_pane = new MoviePane();
}

MainWindow::~MainWindow() {
    delete movie_pane;
}

bool MainWindow::onEvent(SDL_Event* event) {
    if (movie_pane->onEvent(event)) {
        return true;
    }

    return false;
}
void MainWindow::onBackground() {
    movie_pane->onBackground();
}

void MainWindow::onDraw() {
    bool show = true;
    int w, h;
    SDL_GetWindowSize(g_AppGlobal.window, &w, &h);

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(w, h));
    ImGui::Begin("main_window", &show, BG_WINDOW_FLAGS);

    switch (mode) {
    case MainWindowMode::Movies:
        movie_pane->onDraw();
    }

    ImGui::End();
}
}