#pragma once

#include "../playback/video_buffer.h"
#include "base/fragment.h"
#include "core.h"

#include "movie_pane.h"

namespace UI {

enum class MainWindowMode {
    Movies = 1

};

class MainWindow : public Fragment {
    MainWindowMode mode = MainWindowMode::Movies;
    MoviePane* movie_pane;

public:
    MainWindow();
    ~MainWindow();
    bool onEvent(SDL_Event* event) override;
    void onBackground() override;
    void onDraw() override;
};
}