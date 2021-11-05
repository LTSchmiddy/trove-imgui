#include <Python.h>
// #include <boost/python.hpp>

// namespace bpy=boost::python;

#ifdef _WIN64
   #define PY_PATH_DELIMITER L";"
#elif _WIN32
   #define PY_PATH_DELIMITER L";"
#else
    #define PY_PATH_DELIMITER L":"
#endif

bool init_python();
void shutdown_python();