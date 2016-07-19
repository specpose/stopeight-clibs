#!/usr/bin/env python

import os

from distutils.core import setup, Extension

analyzer_wrapper = Extension('stopeight_clibs_analyzer', include_dirs=[os.getcwd()+'/../analyzer/include'],
                   library_dirs=['/usr/lib/x86_64-linux-gnu',os.getcwd()+'/../analyzer/build/debug'],
                   libraries=['stopeight-clibs-analyzer'],
                   sources = ['interfacepython.cpp'])

setup( name='stopeight_clibs_analyzer',
       version='0.1.0',
       description='stopeight-clibs-analyzer: Providing access to Analyzer',
       author='Fassio Blatter',
       license='GNU Lesser General Public License, version 2.1',
       url='http://www.stopeight.com',
       ext_modules= [analyzer_wrapper]
)
