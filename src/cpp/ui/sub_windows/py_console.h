#pragma once

#include <vector>

#include "ui/core.h"
#include "ui/base/fragment.h"
#include "python/py_main.h"


namespace UI {
enum class PyConsoleLineType {
    out = 0,
    err = 1,
    in = 2
};

struct PyConsoleLine {
    PyConsoleLineType type;
    std::string text;
    
    void draw();
};

class PyConsole : public Fragment {
public:

    ImGuiInputTextFlags console_log_flags = 0
        | ImGuiInputTextFlags_ReadOnly
    ;

    ImGuiInputTextFlags console_input_multiline_flags = 0
        | ImGuiInputTextFlags_EnterReturnsTrue
        | ImGuiInputTextFlags_CtrlEnterForNewLine
        | ImGuiInputTextFlags_CallbackCompletion
    ;

    ImGuiInputTextFlags console_input_flags = 0
        | console_input_multiline_flags
        | ImGuiInputTextFlags_CallbackHistory
    ;

    ImGuiWindowFlags log_child_flags = 0
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoSavedSettings
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_HorizontalScrollbar
    ;

    py::module_ m_std_handler;
    py::object custom_stdout;
    py::object custom_stderr;

    py::module_ py_context;
    py::dict console_locals;

    std::string console_input;
    // std::string console_log;

    bool use_multi_line_input = false;

    std::vector<PyConsoleLine*> lines;

    PyConsole();
    ~PyConsole();
    void onBackground() override;
    void addLines(PyConsoleLineType type, std::string text_body);
    // bool onEvent(SDL_Event* event) override;
    void onDraw() override;

    void drawLog(ImVec2 log_size);
    void onSubmit();

    int consoleInputCallback(ImGuiInputTextCallbackData* data);
};
}