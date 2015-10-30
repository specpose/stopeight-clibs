from distutils.core import setup, Extension

legacy_wrapper = Extension('stopeight_clibs_legacy', include_dirs=['/usr/include/qt4','/home/fassio/Desktop/Sources/stopeight-clibs/legacy/include'],
                   library_dirs=['/usr/lib/x86_64-linux-gnu','/home/fassio/Desktop/Sources/stopeight-clibs/legacy'],
                   libraries=['QtCore','stopeight-clibs-legacy'],
                   sources = ['interfacepython.cpp'])

setup( name='stopeight_clibs_legacy',
       version='0.1.0',
       description='stopeight-clibs: Providing access to legacy-style Qt code',
       ext_modules= [legacy_wrapper])
