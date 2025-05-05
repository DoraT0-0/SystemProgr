#include "wordcount.h"
#include <cstring>
#include <cctype>

WORDCOUNT_API int CountWords(const char* str) {
    if (str == nullptr) return 0;

    int count = 0;
    bool inWord = false;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (isspace(str[i])) {
            inWord = false;
        } else if (!inWord) {
            inWord = true;
            ++count;
        }
    }

    return count;
}