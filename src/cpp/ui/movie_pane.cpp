#include "movie_pane.h"

#include <iostream>

namespace UI {

// We're storing the video record again on the native side. This way, we don't need to hold the GIL
// while rendering the UI.
VideoControl::VideoControl(int p_id, std::string p_name) {
    id = p_id;
    name = p_name;
}

void VideoControl::onDraw() {
    std::string label = name + "## id: " + std::to_string(id);
    if (ImGui::CollapsingHeader(label.c_str())) {
        ImGui::Indent();
        ImGui::Text("%s", name.c_str());
        ImGui::Unindent();
    }
}


// MoviePane: 
MoviePane::MoviePane() {
    scan_callback = py::cpp_function([this]() { this->updateDisplay(); });
    updateDisplay();
}

MoviePane::~MoviePane() {

}

bool MoviePane::onEvent(SDL_Event* event) {
    return false;
}

void MoviePane::onBackground() { }

void MoviePane::onDraw() {
    if (ImGui::Button("Test Scan")) {
        py::gil_scoped_acquire gil;
        lib_trove_instance->o.attr("scan_async")(&scan_callback);
    }
    
    ImGui::SameLine();
    if (ImGui::Button("Test Display")) {
        updateDisplay();
    }

    ImGui::Separator();
    for (int i = 0; i < video_data.size(); i++) {
        drawVideoData(&video_data[i]);
    }
}

void MoviePane::drawVideoData(VideoControl* v) {
    v->onDraw();
}

void MoviePane::updateDisplay() {
    py::gil_scoped_acquire gil;
    video_data.clear();

    py::object session = lib_trove_instance->o.attr("get_session")();
    py::list pv = py_main_module->m.attr("get_videos")(session);

    int count = pv.size();

    std::cout << "Count: " << count << std::endl;

    for (int i = 0; i < count; i++) {
        video_data.emplace_back(
            pv[i].attr("id").cast<int>(),
            pv[i].attr("fname").cast<std::string>()
        );
    }

    session.attr("close")();
}
}