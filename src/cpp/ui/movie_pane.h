#pragma once

#include "base/fragment.h"
#include "core.h"
#include "python/py_main.h"

namespace UI {
class MoviePane : public Fragment {
public:
    py::module_ mod;

    MoviePane();
    ~MoviePane();
    bool onEvent(SDL_Event* event) override;
    void onBackground() override;
    void onDraw() override;

    PyObject* test_function_2(PyObject* self, PyObject* args);
};
}