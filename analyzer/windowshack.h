#ifndef WINDOWSHACK_H
#define WINDOWSHACK_H

#ifdef _WIN32 || _WIN64
    #ifdef ANALYZER_LIBRARY
    #  define ANALYZERSHARED_EXPORT __declspec(dllexport)
    #else
    #  define ANALYZERSHARED_EXPORT __declspec(dllimport)
    #endif
#else
    #define ANALYZERSHARED_EXPORT
#endif

#endif // WINDOWSHACK_H
