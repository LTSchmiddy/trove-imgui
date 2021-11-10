#include "movie_pane.h"

#include <iostream>

namespace UI {


// We're storing the video record again on the native side. This way, we don't need to hold the GIL 
// while rendering the UI. 
VideoUIData::VideoUIData(int p_id, std::string p_mrl, std::string p_name, std::string p_desc, std::string p_source) {
    id = p_id;
    mrl = p_mrl;
    name = p_name;
    desc = p_desc;
    source = p_source;
}


MoviePane::MoviePane() { 
    scan_callback = py::cpp_function([this](){this->updateDisplay();});
}

MoviePane::~MoviePane() { }

bool MoviePane::onEvent(SDL_Event* event) {
    return false;
}

void MoviePane::onBackground() { }

void MoviePane::onDraw() {
    if (ImGui::Button("Test Scan")) {
        py::gil_scoped_acquire gil;
        lib_trove_instance->o.attr("scan_async")(&scan_callback);
        
        py_simple_error_check("fn_method_call_error");

    }

    if (ImGui::Button("Test Display")) {
        updateDisplay();
    }

    for (int i = 0; i < video_data.size(); i++) {
        drawVideoData(&video_data[i]);
    }
}

void MoviePane::drawVideoData(VideoUIData* v) {
    std::string label = v->name + " ## id: " + std::to_string(v->id);
    

    if (ImGui::Button(label.c_str())) {
        std::cout << v->name << std::endl;
    }
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
            pv[i].attr("mrl").cast<std::string>(),
            pv[i].attr("fname").cast<std::string>(),
            pv[i].attr("source").cast<std::string>(),
            pv[i].attr("description").cast<std::string>()
        );
    }

    session.attr("close")();
}
}