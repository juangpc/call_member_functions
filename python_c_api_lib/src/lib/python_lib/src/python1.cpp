#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "calls.hpp"

extern "C" {
  void call1(int a) {
    calls::callback1(a);
  }
 void call2(int a) {
    calls::callback2(a);
  }
 void call3(int a) {
    calls::callback3(a);
  }
}

static PyObject* callback1(PyObject* self, PyObject* args) {
  int value;
  if (!PyArg_ParseTuple(args, "i", &value)) return NULL;
  call1(value);
  return PyLong_FromLong(value);
}

static PyObject* callback2(PyObject* self, PyObject* args) {
  int value;
  if (!PyArg_ParseTuple(args, "i", &value)) return NULL;
  call2(value);
  return PyLong_FromLong(value);
}

static PyObject* callback3(PyObject* self, PyObject* args) {
  int value;
  if (!PyArg_ParseTuple(args, "i", &value)) return NULL;
  call3(value);
  return PyLong_FromLong(value);
}

static PyMethodDef CallbackMethods[] = {
  {"callback1", callback1, METH_VARARGS, "print callback1 text"},
  {"callback2", callback2, METH_VARARGS, "print callback2 text"},
  {"callback3", callback3, METH_VARARGS, "print callback3 text"},
  {NULL, NULL, 0, NULL}
};

#if PY_MAJOR_VERSION >= 3
/* module initialization */
/* Python version 3*/
static struct PyModuleDef cModPyDem = {
    PyModuleDef_HEAD_INIT,
    "callback_module", "Some documentation",
    -1,
    CallbackMethods
};

PyMODINIT_FUNC PyInit_callback_module(void) {
  return PyModule_Create(&cModPyDem); 
}
#else
/* module initialization */ /* Python version 2 */ 
PyMODINIT_FUNC initcallback_module(void) {
  (void) Py_InitModule("callback_module", CallbackMethods);
}
#endif

