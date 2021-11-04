#include "init.h"

#include <iostream>

#include <boost/dll.hpp>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

void init_python() {
    fs::path lib_dir = boost::dll::program_location().parent_path().append("Lib");
    fs::path site_dir = boost::dll::program_location().parent_path().append("Lib/site-packages");
    fs::path dll_dir = boost::dll::program_location().parent_path().append("DLLs");

    fs::path py_dir = boost::dll::program_location().parent_path().append("py");

    std::wstring delim = PY_PATH_DELIMITER;
    std::wstring py_path;
    if(const char* env_p = std::getenv("TROVE_PY_SCRIPTS_DIR")) {
        std::string env_p_string(env_p);
        std::wstring env_p_wstring;
        env_p_wstring.assign(env_p_string.begin(), env_p_string.end());

        py_path = lib_dir.wstring() + delim + dll_dir.wstring() + delim + site_dir.wstring() + delim + env_p_wstring;
    } else {
        py_path = lib_dir.wstring() + delim + dll_dir.wstring() + delim + site_dir.wstring() + delim + py_dir.wstring();
    }

    Py_SetPath(py_path.c_str());
    Py_Initialize();

    std::wcout << L"Py Path: " << Py_GetPath() << std::endl;

    PyImport_ImportModule("hello");
}