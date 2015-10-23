#ifndef WINDOWSHACK2_H
#define WINDOWSHACK2_H

#ifdef _WIN32 || _WIN64
    #ifdef ANALYZER_LIBRARY
    #  define ANALYZERWRAPPERSSHARED_EXPORT __declspec(dllexport)
    #else
    #  define ANALYZERWRAPPERSSHARED_EXPORT __declspec(dllimport)
    #endif
#else
    #define ANALYZERWRAPPERSSHARED_EXPORT
#endif

#endif // WINDOWSHACK2_H
