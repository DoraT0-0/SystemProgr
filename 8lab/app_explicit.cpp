#include <iostream>
#include <windows.h>

typedef int (*CountWordsFunc)(const char*);

int main() {
    HMODULE hDll = LoadLibraryA("wordcount.dll");
    if (hDll == nullptr) {
        std::cerr << "Failed to load DLL" << std::endl;
        return 1;
    }

    CountWordsFunc CountWords = (CountWordsFunc)GetProcAddress(hDll, "CountWords");
    if (CountWords == nullptr) {
        std::cerr << "Failed to get function address" << std::endl;
        FreeLibrary(hDll);
        return 1;
    }

    const char* str = "This is a test string.";
    int wordCount = CountWords(str);
    std::cout << "Number of words: " << wordCount << std::endl;

    FreeLibrary(hDll);
    return 0;
}