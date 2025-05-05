#include <windows.h>
#include <stdio.h>

#define YUCTL_MAKE_SYSTEM_CRASH 0x800
#define YUCTL_TOUCH_PORT_378 0x801
#define YUCTL_SEND_BYTE_TO_USER 0x802

int main() {
    HANDLE hDevice;
    DWORD bytesReturned;
    char buffer[1024];

    // Открытие устройства
    hDevice = CreateFile(
        L"\\\\.\\MyDevice",  // Имя устройства
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hDevice == INVALID_HANDLE_VALUE) {
        printf("Не удалось открыть устройство.\n");
        return 1;
    }

    // Операция YUCTL_MAKE_SYSTEM_CRASH
    if (!DeviceIoControl(
        hDevice,
        YUCTL_MAKE_SYSTEM_CRASH,
        NULL,
        0,
        NULL,
        0,
        &bytesReturned,
        NULL
    )) {
        printf("Не удалось выполнить операцию YUCTL_MAKE_SYSTEM_CRASH.\n");
    } else {
        printf("Операция YUCTL_MAKE_SYSTEM_CRASH выполнена успешно.\n");
    }

    // Операция YUCTL_TOUCH_PORT_378
    if (!DeviceIoControl(
        hDevice,
        YUCTL_TOUCH_PORT_378,
        NULL,
        0,
        NULL,
        0,
        &bytesReturned,
        NULL
    )) {
        printf("Не удалось выполнить операцию YUCTL_TOUCH_PORT_378.\n");
    } else {
        printf("Операция YUCTL_TOUCH_PORT_378 выполнена успешно.\n");
    }

    // Операция YUCTL_SEND_BYTE_TO_USER
    char byteToSend = 'A';
    if (!DeviceIoControl(
        hDevice,
        YUCTL_SEND_BYTE_TO_USER,
        &byteToSend,
        sizeof(byteToSend),
        NULL,
        0,
        &bytesReturned,
        NULL
    )) {
        printf("Не удалось выполнить операцию YUCTL_SEND_BYTE_TO_USER.\n");
    } else {
        printf("Операция YUCTL_SEND_BYTE_TO_USER выполнена успешно.\n");
    }

    // Закрытие устройства
    CloseHandle(hDevice);

    return 0;
}