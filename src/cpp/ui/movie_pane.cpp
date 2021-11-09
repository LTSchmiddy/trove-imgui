#include "movie_pane.h"

#include <functional>


namespace UI {
    static PyObject* test_function (PyObject *self, PyObject *args) {

        return PyLong_FromLong(99);
    }

    MoviePane::MoviePane() {

        std::function<PyObject*(PyObject*, PyObject*)> F([this](PyObject *self, PyObject *args){ return PyLong_FromLong(99); });

        main_window_methods_def = new PyMethodDef[2]{
            {"test_function", test_function, METH_VARARGS, "Testing 1 2 3..."},
            // {"test_function",  [this](PyObject *self, PyObject *args)-> PyObject* {}, METH_VARARGS, "Testing 1 2 3..."},
            {NULL, NULL, 0, NULL}        /* Sentinel */
        };

        main_window_module_def = {
            PyModuleDef_HEAD_INIT,
            "trove_imgui",   /* name of module */
            NULL, /* module documentation, may be NULL */
            -1,       /* size of per-interpreter state of the module, 
                        or -1 if the module keeps state in global variables. */
            main_window_methods_def
        };
        main_window_module = PyModule_Create(&main_window_module_def);
    }

    MoviePane::~MoviePane(){
        Py_DECREF(main_window_module);
    }

    bool MoviePane::onEvent(SDL_Event* event){
        return false;
    }

    void MoviePane::onBackground(){}

    void MoviePane::onDraw(){
        if (ImGui::Button("Test Scan")) {
            py::gil_scoped_acquire gil;
            lib_trove_instance->m.attr("test_method")();
        }

        if (ImGui::Button("Test Module")) {

        }

    }

    // PyObject* MoviePane::test_function_2 (PyObject *self, PyObject *args) {

    // }
}