#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <clocale>
#include <string>

// Функция для включения привилегии SeDebugPrivilege
BOOL EnableDebugPrivilege() {
    HANDLE hToken;
    LUID luid;
    TOKEN_PRIVILEGES tkp;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        return FALSE;
    }

    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid)) {
        CloseHandle(hToken);
        return FALSE;
    }

    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Luid = luid;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL)) {
        CloseHandle(hToken);
        return FALSE;
    }

    CloseHandle(hToken);
    return TRUE;
}

// Функция для получения информации о процессе
void GetProcessInfo(DWORD processId) {
    if (!EnableDebugPrivilege()) {
        std::cerr << "Не удалось включить привилегию SeDebugPrivilege." << std::endl;
        return;
    }

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if (hProcess == NULL) {
        DWORD error = GetLastError();
        std::cerr << "Не удалось открыть процесс с PID: " << processId << ". Ошибка: " << error << std::endl;
        return;
    }

    // Получение приоритета процесса
    DWORD priorityClass = GetPriorityClass(hProcess);
    if (priorityClass == 0) {
        std::cerr << "Не удалось получить приоритет процесса с PID: " << processId << std::endl;
        CloseHandle(hProcess);
        return;
    }

    // Получение количества потоков
    DWORD threadCount;
    if (!GetProcessTimes(hProcess, nullptr, nullptr, nullptr, nullptr)) {
        std::cerr << "Не удалось получить количество потоков процесса с PID: " << processId << std::endl;
        CloseHandle(hProcess);
        return;
    }

    // Получение времени работы процесса
    FILETIME creationTime, exitTime, kernelTime, userTime;
    if (!GetProcessTimes(hProcess, &creationTime, &exitTime, &kernelTime, &userTime)) {
        std::cerr << "Не удалось получить время работы процесса с PID: " << processId << std::endl;
        CloseHandle(hProcess);
        return;
    }

    // Преобразование времени в секунды
    ULARGE_INTEGER kernelTimeUI, userTimeUI;
    kernelTimeUI.LowPart = kernelTime.dwLowDateTime;
    kernelTimeUI.HighPart = kernelTime.dwHighDateTime;
    userTimeUI.LowPart = userTime.dwLowDateTime;
    userTimeUI.HighPart = userTime.dwHighDateTime;
    double totalTime = (kernelTimeUI.QuadPart + userTimeUI.QuadPart) / 10000000.0;

    // Вывод информации
    std::cout << "Процесс с PID: " << processId << std::endl;
    std::cout << "Приоритет: " << priorityClass << std::endl;
    std::cout << "Количество потоков: " << threadCount << std::endl;
    std::cout << "Время работы (секунды): " << totalTime << std::endl;

    CloseHandle(hProcess);
}

// Функция для получения информации о загрузке процессора
void GetCPUUsage() {
    FILETIME idleTime, kernelTime, userTime;
    if (!GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
        std::cerr << "Не удалось получить информацию о загрузке процессора." << std::endl;
        return;
    }

    ULARGE_INTEGER idleTimeUI, kernelTimeUI, userTimeUI;
    idleTimeUI.LowPart = idleTime.dwLowDateTime;
    idleTimeUI.HighPart = idleTime.dwHighDateTime;
    kernelTimeUI.LowPart = kernelTime.dwLowDateTime;
    kernelTimeUI.HighPart = kernelTime.dwHighDateTime;
    userTimeUI.LowPart = userTime.dwLowDateTime;
    userTimeUI.HighPart = userTime.dwHighDateTime;

    double totalTime = (kernelTimeUI.QuadPart + userTimeUI.QuadPart) / 10000000.0;
    double idleTimeSec = idleTimeUI.QuadPart / 10000000.0;
    double usage = (totalTime - idleTimeSec) / totalTime * 100.0;

    std::cout << "Загрузка процессора: " << usage << "%" << std::endl;
}

int main() {
    // Настройка локали и кодировки
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251); // Установка кодовой страницы для ввода
    SetConsoleOutputCP(1251); // Установка кодовой страницы для вывода

    // Получение списка процессов
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        std::cerr << "Не удалось создать снимок процессов." << std::endl;
        return 1;
    }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        std::cerr << "Не удалось получить первый процесс." << std::endl;
        CloseHandle(hProcessSnap);
        return 1;
    }

    do {
        GetProcessInfo(pe32.th32ProcessID);
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);

    // Получение информации о загрузке процессора
    GetCPUUsage();

    return 0;
}