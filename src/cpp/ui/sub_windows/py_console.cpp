#include "py_console.h"

#include <algorithm>
#include <functional>
#include <iostream>

namespace UI {

void PyConsoleLine::draw() {
    ImGui::Text("%s", text.c_str());
}

PyConsole::PyConsole() {
    py::gil_scoped_acquire gil;
    m_std_handler = py::module_::import("std_handler");
    custom_stdout = m_std_handler.attr("custom_stdout");
    custom_stderr = m_std_handler.attr("custom_stderr");

    // py_context = create_py_module("py_console_context");
    console_locals = py::dict();
}

PyConsole::~PyConsole() {
    for (int i = 0; i < lines.size(); i++) {
        delete lines.at(i);
    } 
}

void PyConsole::onBackground() {
    py::gil_scoped_acquire gil;

    std::string out_body = custom_stdout.attr("get_appended_stream")().cast<std::string>();
    addLines(PyConsoleLineType::out, out_body);

    std::string err_body = custom_stderr.attr("get_appended_stream")().cast<std::string>();
    addLines(PyConsoleLineType::err, err_body);
}

void PyConsole::addLines(PyConsoleLineType type, std::string text_body) {
    std::string buffer = "";
    for (int index = 0; index < text_body.length(); index++) {
        char& i = text_body.at(index);

        if (i != '\n') {
            buffer += i;
            continue;
        }

        PyConsoleLine* line = new PyConsoleLine {type, buffer};
        lines.emplace_back(line);
        buffer.clear();
    }
    // Dump any remainder:
    if (buffer.length() > 0) {
        PyConsoleLine* line = new PyConsoleLine {type, buffer};
        lines.emplace_back(line);
    }
}

void PyConsole::onDraw() {
    // ImVec2 window_size = ImGui::GetWindowSize();
    ImVec2 window_size = ImGui::GetContentRegionAvail();
    float line_size = ImGui::GetFontSize();

    int input_lines = std::count(console_input.begin(), console_input.end(), '\n');
    ImVec2 input_size = ImVec2(window_size.x, std::max(line_size * (input_lines + 1), line_size * 1.5f));

    ImVec2 log_size = ImVec2(window_size.x, window_size.y - (input_size.y + line_size * 1));

    drawLog(log_size);
    if (use_multi_line_input) {
        if (ImGui::InputTextMultiline(
                "##python_console_input_multi_line", 
                &console_input, 
                input_size, 
                console_input_multiline_flags, 
                [](ImGuiInputTextCallbackData* data) { 
                    return ((PyConsole*)data->UserData)->consoleInputCallback(data);
                }, 
                // py_console_text_callback, 
                (void*)this
        )) {
            onSubmit();
        }
    } else {
        ImGui::PushItemWidth(input_size.x);
        if (ImGui::InputText(
            "##python_console_input",
            &console_input,
            console_input_flags,
            [](ImGuiInputTextCallbackData* data) { 
                return ((PyConsole*)data->UserData)->consoleInputCallback(data);
            },
            (void*)this
        )) {
            onSubmit();
        }
        ImGui::PopItemWidth();
    }
}

void PyConsole::drawLog(ImVec2 log_size) {
    ImGui::BeginChild("##python_console_log", log_size, false, log_child_flags);
    for (int i = 0; i < lines.size(); i++) {
        lines.at(i)->draw();
    }
    ImGui::EndChild();
}

void PyConsole::onSubmit() {
    std::cout << "Console Input: " << console_input << std::endl;
    console_input.clear();
}

int PyConsole::consoleInputCallback(ImGuiInputTextCallbackData* data) {
    std::cout << "Callback Data Pointer: " << data << std::endl;

    return 1;
}
}