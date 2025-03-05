#include <iostream>
#include <string>
using namespace std;

void addslashes(string& str){
    string result;

    for(size_t i = 0;i < str.length(); ++i){
        if(str[i] == '\'' || str[i] == '"'){
            result += '\\';
        }
        result += str[i];
    }

    str = result;
}

void ltrim(string &str){
    size_t start = str.find_first_not_of(" ");
    if(start != string::npos){
        str.erase(0, start);
    }
}

int comparestrings(const string& str1, const string& str2) {
    if (str1.size() < str2.size()) return 1;
    else if (str1.size() > str2.size()) return 2;
    else return 3;
}

bool containsOnlyABC(const string& str){
    for (char c : str) {
        if (c != 'a' && c != 'b' && c != 'c') {
            return false;
        }
    }
    return true;
}

int main(){
    string str1= "  j 'asd";
    string str2 = "  j asd";
    string str3 = "abc";

    cout << containsOnlyABC(str3) << endl;
    cout << comparestrings(str1, str2) << endl;
    addslashes(str1);
    ltrim(str1);

    cout << str1;

    return 0;
}