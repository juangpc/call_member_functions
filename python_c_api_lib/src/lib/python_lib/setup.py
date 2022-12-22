#from distutils.core import setup, Extension
from setuptools import setup, Extension

# define the extension module
callback_module = Extension('callback_module',
        sources=['src/python1.cpp'],
        #libraries=['libcalls.a'],
        include_dirs=['include','../calls/include'],
        library_dirs=['.'],
        extra_objects=['libcalls.a'],
        extra_link_args=['-static'],
        language='c++')

# run the setup
setup(name = 'callback_module',
      ext_modules = [callback_module])

#by default python will want dynamic libraries. but we can have 
#static linking to a code with "extra objects" and "extra link args" arguments.

#python setup.py build
#python setup.py install

#pythonX.Y-config --cflags will give you the recommended flags when compiling
#pythonX.Y-config --ldflags --embed will give you the recommended flags when linking

#this is where we can get information from when deciding on the flags. 
#once we get these flags going, we'll be able to compile with any compiler

