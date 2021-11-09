#include "py_main.h"

#include <iostream>

#include <boost/dll.hpp>
#include <boost/filesystem.hpp>

#include "../main.h"

namespace fs = boost::filesystem;

// Private values:
// PyObject* debug_module;
pyow* debug_module;

// Public values:
// PyObject* main_module;
// PyObject* lib_trove_instance;
pyow* main_module;
pyow* lib_trove_instance;

// We own these all of these references.

bool py_simple_error_check(std::string error_message)
{
    if (PyErr_Occurred() != NULL) {
        // This implies that an error has occured.

        PyErr_Print();
        std::cerr << error_message << "\n";

        return true;
    }

    return false;
}

bool init_python(int argc, char** argv)
{

    // Getting Paths for various python components:
    fs::path lib_dir = boost::dll::program_location().parent_path().append("Lib");
    fs::path site_dir = boost::dll::program_location().parent_path().append("Lib/site-packages");
    fs::path dll_dir = boost::dll::program_location().parent_path().append("DLLs");

    fs::path py_dir = boost::dll::program_location().parent_path().append("py");

    // Assembling the Python Path string:
    std::wstring delim = PY_PATH_DELIMITER;
    std::wstring py_path;
    // For development purposes, we can manually override where trove
    // will look for the application python scripts, using an env variable.
    if (const char* env_py_dir = std::getenv("TROVE_PY_SCRIPTS_DIR")) {
        std::string env_p_string(env_py_dir);
        std::wstring env_p_wstring;
        env_p_wstring.assign(env_p_string.begin(), env_p_string.end());
        py_path = lib_dir.wstring() + delim + dll_dir.wstring() + delim + site_dir.wstring() + delim + env_p_wstring;
    } else {
        py_path = lib_dir.wstring() + delim + dll_dir.wstring() + delim + site_dir.wstring() + delim + py_dir.wstring();
    }

    // Starting up the interpreter:

    Py_SetPath(py_path.c_str());
    std::wcout << L"Py Path: " << Py_GetPath() << std::endl;

    py::initialize_interpreter(true, argc, argv, true);

    // If we were told to use the python debugger, start that now:
    if (const char* env_port = std::getenv("TROVE_PY_DEBUG_PORT")) {
        std::cout << "Debug Port: " << env_port << std::endl;

        // debug_module = PyImport_ImportModule("debug"); // New Reference
        debug_module = new pyow { py::module_::import("debug") }; // New Reference
        // debug_module.inc_ref();
        py_simple_error_check("Python debug module has failed to load. Skipping...");
    }

    // main_module = PyImport_ImportModule("main"); // New Reference
    main_module = new pyow { py::module_::import("main") }; // New Reference
    // main_module.inc_ref();

    if (py_simple_error_check("FATAL ERROR: Python 'main' module has failed to load.")) {
        return false;
    }

    // Getting important functions:
    lib_trove_instance = new pyow { main_module->m.attr("init")() };
    lib_trove_instance->m.attr("test_method")();
    // lib_trove_instance.inc_ref();

    if (py_simple_error_check("FATAL ERROR: Python initialization code has failed.")) {
        return false;
    }

    return true;
}

// Cleaning up Python:
void shutdown_python()
{
    if (debug_module != NULL) {
        delete debug_module;
    }

    main_module->m.attr("shutdown");

    delete lib_trove_instance;
    delete main_module;

    py::finalize_interpreter();
}