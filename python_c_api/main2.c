#define PY_SSIZE_T_CLEAN
#include <Python.h>

int main(int argc, char *argv[])
{
  PyObject *pName = NULL;
  PyObject *pModule = NULL;
  PyObject *pFunc = NULL;
  PyObject *pValue = NULL;

  Py_Initialize();
  // PySys_SetArgv(0, NULL); // current directory added to path
  PyConfig config;
  PyConfig_InitPythonConfig(&config);
  config.module_search_paths_set = 1;
  PyWideStringList_Append(&config.module_search_paths, L".");
  Py_InitializeFromConfig(&config);

  pName = PyUnicode_FromString(argv[1]);
  pModule = PyImport_Import(pName);
  Py_XDECREF(pName);

  pFunc = PyObject_GetAttrString(pModule, argv[2]);
  pValue = PyObject_CallNoArgs(pFunc); // actual call to the fcn

  Py_XDECREF(pValue);
  Py_XDECREF(pFunc);
  Py_XDECREF(pModule);

  Py_Finalize();
  return 0;
}

