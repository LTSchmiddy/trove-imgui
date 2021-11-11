#include "py_console.h"

#include <iostream>
#include <functional>

namespace UI {
void PyConsole::onDraw() {
    std::function fn = [this](ImGuiInputTextCallbackData data) -> ImGuiInputTextCallback {
        return this->text_callback(data);
    };

    if (ImGui::InputText(
        "##python_text_input",
        &input_text,
        0
            | ImGuiInputTextFlags_EnterReturnsTrue
            | ImGuiInputTextFlags_CallbackCompletion
            | ImGuiInputTextFlags_CallbackHistory
        ,
        text_callback

    )) {
        std::cout << "Input Text: " << input_text << std::endl;
    }
}
} 