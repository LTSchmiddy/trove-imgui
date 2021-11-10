#pragma once

#include <functional>
#include <vector>

#include "base/fragment.h"
#include "core.h"
#include "python/py_main.h"

namespace UI {
class VideoControl : public Fragment {
public:

    int id;
    std::string name;

    VideoControl(int p_id, std::string name);
    void onDraw() override;
    
private:
    bool expanded = false;

};

class MoviePane : public Fragment {
public:
    MoviePane();
    ~MoviePane();
    bool onEvent(SDL_Event* event) override;
    void onBackground() override;
    void onDraw() override;

    void drawVideoData(VideoControl* v);

private:
    std::vector<VideoControl> video_data;
    py::cpp_function scan_callback;
    void updateDisplay();
};
}