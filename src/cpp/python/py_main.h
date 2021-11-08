#pragma once

#include <Python.h>
#include <string>
// #include <boost/python.hpp>

// namespace bpy=boost::python;

#ifdef _WIN64
   #define PY_PATH_DELIMITER L";"
#elif _WIN32
   #define PY_PATH_DELIMITER L";"
#else
    #define PY_PATH_DELIMITER L":"
#endif

bool py_simple_error_check(std::string error_message = "");
bool init_python();
void shutdown_python();