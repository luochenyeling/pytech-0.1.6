from setuptools import setup, Extension  
import os  
import sys  
  
pytech = Extension('pytech',  
                           sources=['src/pytech.cpp'],  
                           include_dirs=[os.path.join(os.getcwd(), 'include'),os.path.join(os.getcwd(), 'src')],  
                           language='c++')  
  
setup(name='pytech',  
      version='0.1.6',  
      description='Python function package of technical indicators and patterns implemented by C++',  
      ext_modules=[pytech],  
      zip_safe=False
      )