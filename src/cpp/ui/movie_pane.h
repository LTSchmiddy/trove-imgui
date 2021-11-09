#pragma once

#include "base/fragment.h"
#include "core.h"
#include "python/py_main.h"

namespace UI {
class MoviePane : public Fragment {
public:
    PyMethodDef* main_window_methods_def;
    PyModuleDef main_window_module_def;

    PyObject* main_window_module;

    MoviePane();
    ~MoviePane();
    bool onEvent(SDL_Event* event) override;
    void onBackground() override;
    void onDraw() override;

    PyObject* test_function_2(PyObject* self, PyObject* args);
};
}