#pragma once

#include <functional>
#include <vector>

#include "base/fragment.h"
#include "core.h"
#include "python/py_main.h"

namespace UI {
struct VideoUIData {
    int id;
    std::string mrl;
    std::string name;
    std::string desc;
    std::string source;

    VideoUIData(int p_id, std::string p_mrl, std::string name, std::string desc, std::string source);
};

class MoviePane : public Fragment {
public:
    MoviePane();
    ~MoviePane();
    bool onEvent(SDL_Event* event) override;
    void onBackground() override;
    void onDraw() override;

    void drawVideoData(VideoUIData *v);
private:
    std::vector<VideoUIData> video_data;
    py::cpp_function scan_callback;
    void updateDisplay();
};
}