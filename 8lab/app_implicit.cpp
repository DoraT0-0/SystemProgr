#include <iostream>
#include "wordcount.h"

int main() {
    const char* str = "This is a test string.";
    int wordCount = CountWords(str);
    std::cout << "Number of words: " << wordCount << std::endl;
    return 0;
}