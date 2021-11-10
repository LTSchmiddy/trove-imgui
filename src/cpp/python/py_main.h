#pragma once

// Includes:
#include <Python.h>
#include <pybind11/embed.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <string>

// Namespaces
namespace py = pybind11;

// Macros:
#ifdef _WIN64
#define PY_PATH_DELIMITER L";"
#elif _WIN32
#define PY_PATH_DELIMITER L";"
#else
#define PY_PATH_DELIMITER L":"
#endif

#define PY_ENSURE_GIL PyGILState_STATE _gil_state = PyGILState_Ensure();
#define PY_RELEASE_GIL PyGILState_Release(_gil_state);

#define PY_BEGIN_GIL_BLOCK \
    {                      \
        PyGILState_STATE _gil_state = PyGILState_Ensure();
#define PY_END_GIL_BLOCK            \
    PyGILState_Release(_gil_state); \
    }

// Apparently, pybind11 has problems when py::objects are still in memory after interpreter shutdown.
// This makes it a LOT easier to set py::objects as pointers, so they can be deleted manually.
struct pyow {
    py::object o;
};
struct pymw {
    py::module_ m;
};

// Variables:
// extern PyObject* main_module;
// extern PyObject* lib_trove_instance;

extern pymw* py_main_module;
extern pyow* lib_trove_instance;

// Functions:
bool py_simple_error_check(std::string error_message = "");
bool init_python(int argc, char** argv);
void shutdown_python();

py::module_ create_py_module(const char* name);