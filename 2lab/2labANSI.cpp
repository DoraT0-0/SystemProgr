#include <iostream>
#include <cstring>
using namespace std;

void addslashes(char* str){
    char temp[strlen(str)*2+1];
    int j = 0;

    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == '\'' || str[i] == '"'){
            temp[j++] = '\\';
        }
        temp[j++] = str[i];
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

void ltrim(char* str){
    size_t len = strlen(str);
    size_t start = 0;

    while(start < len && isspace(str[start])){
        ++start;
    }
    if(start > 0){
        memmove(str, str + start, len - start + 1);
    }
}

int comparestrings(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    
    if (len1 < len2) return 1;
    else if (len1 > len2) return 2;
    else return 3;
}

bool containsOnlyABC(const char* str) {
    while (*str != '\0') {
        char currentChar = *str;
        if(currentChar != 'a' && currentChar != 'b' && currentChar != 'c') {
            return false;
        }
        str++;
    }
    return true; 
}

int countWords(const char* str) {
    int count = 0;
    bool inWord = false;

    while (*str != '\0') {
        if (*str != ' ') {
            if (!inWord) {
                count++;
                inWord = true;
            }
        } else {
            inWord = false;
        }
        str++;
    };
    return count;
}

int main(){
    char str1[20] = "  hello 'wor\"ld";
    char str2[20] = "  j asd";

    cout << countWords(str1) << endl;
    cout << containsOnlyABC(str1) << endl;
    cout << comparestrings(str1, str2) << endl;
    addslashes(str1);
    ltrim(str1);
    cout << endl;
    for(int i = 0; str1[i] != '\0'; i++){
        cout << str1[i];
    }
    cout << endl;

    return 0;

}