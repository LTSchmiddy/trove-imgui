#include "movie_pane.h"

#include <iostream>
#include <functional>

namespace UI {
static PyObject* test_function(PyObject* self, PyObject* args) {

    return PyLong_FromLong(99);
}

MoviePane::MoviePane() { }

MoviePane::~MoviePane() {
    mod = create_py_module("test_mod");

    mod.def("test_func", std::function<void(std::string)>([this](std::string x) {std::cout << x;}));
}

bool MoviePane::onEvent(SDL_Event* event) {
    return false;
}

void MoviePane::onBackground() { }

void MoviePane::onDraw() {
    if (ImGui::Button("Test Scan")) {
        py::gil_scoped_acquire gil;
        lib_trove_instance->o.attr("scan_all")(mod.attr("test_func"));
    }

    if (ImGui::Button("Test Module")) {

    }
}

// PyObject* MoviePane::test_function_2 (PyObject *self, PyObject *args) {

// }
}