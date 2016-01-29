#!/usr/bin/env python

import os

from distutils.core import setup, Extension

legacy_wrapper = Extension('stopeight_clibs_legacy', include_dirs=['/usr/include/qt4',os.getcwd()+'/../legacy/include'],
                   library_dirs=['/usr/lib/x86_64-linux-gnu',os.getcwd()+'/../legacy-build'],
                   libraries=['QtCore','QtGui','stopeight-clibs-legacy'],
                   sources = ['interfacepython.cpp'])

setup( name='stopeight_clibs_legacy',
       version='0.1.0',
       description='stopeight-clibs-legacy: Providing access to Qt based Stroke Analyzer',
       author='Fassio Blatter',
       license='GNU Lesser General Public License, version 2.1',
       url='http://www.stopeight.com',
       ext_modules= [legacy_wrapper]
)
