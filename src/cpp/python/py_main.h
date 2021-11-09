#pragma once

#include <Python.h>
#include <string>

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

#define PY_BEGIN_GIL_BLOCK {PyGILState_STATE _gil_state = PyGILState_Ensure();
#define PY_END_GIL_BLOCK PyGILState_Release(_gil_state);}

// Variables:
extern PyObject* main_module;
extern PyObject* lib_trove_instance;

// Functions:
bool py_simple_error_check(std::string error_message = "");
bool init_python();
void shutdown_python();