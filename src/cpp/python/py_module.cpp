#include "py_module.h"
#include "py_main.h"


static PyObject* test_function (PyObject *self, PyObject *args) {

    return PyLong_FromLong(99);
}

static PyMethodDef trove_imgui_methods[] = {
    {"test_function",  test_function, METH_VARARGS, "Testing 1 2 3..."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef trove_imgui_module = {
    PyModuleDef_HEAD_INIT,
    "trove_imgui",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module, 
                or -1 if the module keeps state in global variables. */
    trove_imgui_methods
};

PyMODINIT_FUNC PyInit_trove_imgui(void) {
    PyObject *m;

    m = PyModule_Create(&trove_imgui_module);
    if (m == NULL) {
        return NULL;
    }

    return m;
}