#ifndef WORDCOUNT_H
#define WORDCOUNT_H

#ifdef _WIN32
    #ifdef WORDCOUNT_EXPORTS
        #define WORDCOUNT_API __declspec(dllexport)
    #else
        #define WORDCOUNT_API __declspec(dllimport)
    #endif
#else
    #define WORDCOUNT_API
#endif

extern "C" WORDCOUNT_API int CountWords(const char* str);

#endif // WORDCOUNT_H