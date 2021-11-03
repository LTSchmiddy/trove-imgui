#include "../main.h"
#include "main_window.h"

// #include <vlc.hpp>

namespace UI {
    MainWindow::MainWindow() {
        loaded_media = VLC::Media(*APP_GLOBAL.vlc, videoPath.c_str(), VLC::Media::FromType::FromPath);
        player = VLC::MediaPlayer(loaded_media);
        vb = new VideoBuffer(&player);
    }

    MainWindow::~MainWindow() {
        delete vb;
        player.stopAsync();
    }

    void MainWindow::onDraw() {
        bool show = true;
        int w, h;
        SDL_GetWindowSize(APP_GLOBAL.window, &w, &h);

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(w, h));
        ImGui::Begin("main_window", &show, BG_WINDOW_FLAGS);

        if (player.isPlaying()){
            if (ImGui::Button("Pause")){
                player.pause();
            }
        } else {
            if (ImGui::Button("Play")){
                player.play();
            }
        }

        if (ImGui::Button("Add Intf")){
            APP_GLOBAL.vlc->addIntf("");
        }

        // if (render->bufferMutex.try_lock()) {
            
        // }
        vb->render();
        ImGui::Image(vb->as_imgui_image(), ImVec2(320, 240));

        ImGui::End();
    }
}