#include <windows.h>
#include <iostream>
#include <string>

void FormatMessageAndOutput(LPCWSTR lpszFunction) {
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError();

    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&lpMsgBuf,
        0, NULL);

    // Создаем сообщение, используя wchar_t
    wchar_t message[MAX_PATH];
    swprintf_s(message, MAX_PATH, L"%s in %s", (LPWSTR)lpMsgBuf, lpszFunction);

    MessageBoxW(NULL, message, L"Error", MB_OK | MB_ICONERROR);

    LocalFree(lpMsgBuf);
}

int main() {
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    // Указываем имя мьютекса
    LPCWSTR mutexName = L"MyMutex";

    HANDLE hMutex = CreateMutexW(&sa, FALSE, mutexName);
    if (hMutex == NULL) {
        FormatMessageAndOutput(L"CreateMutex");
        return 1;
    }

    std::cout << "Mutex created successfully." << std::endl;

    HANDLE hMutexDup;
    if (!DuplicateHandle(GetCurrentProcess(), hMutex, GetCurrentProcess(), &hMutexDup, 0, FALSE, DUPLICATE_SAME_ACCESS)) {
        FormatMessageAndOutput(L"DuplicateHandle");
        return 1;
    }

    std::cout << "Handle duplicated successfully." << std::endl;

    if (hMutex == hMutexDup) {
        std::cout << "Original handle and duplicated handle are equal." << std::endl;
    } else {
        std::cout << "Original handle and duplicated handle are not equal." << std::endl;
    }


    HANDLE hMutexCheck = OpenMutexW(MUTEX_ALL_ACCESS, FALSE, mutexName);
    if (hMutexCheck == NULL) {
        FormatMessageAndOutput(L"OpenMutex");
    } else {
        std::cout << "Mutex still exists." << std::endl;
        CloseHandle(hMutexCheck);
    }

    CloseHandle(hMutex);
    CloseHandle(hMutexDup);

    return 0;
}