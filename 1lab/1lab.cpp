#include <windows.h>
#include <iostream>
using namespace std;

void printUpTime(){
    DWORD tickCount = GetTickCount();
    long long milliseconds = tickCount % 1000LL;
    long long totalSeconds = tickCount / 1000LL;
    long days = totalSeconds / (24 * 3600);
    totalSeconds %= (24 * 3600);
    long hours = totalSeconds / 3600;
    totalSeconds %= 3600;
    long minutes = totalSeconds / 60;
    totalSeconds %= 60;

    cout << "System operation time:\n"
              << days << " days, "
              << hours << " hours, "
              << minutes << " minutes, "
              << totalSeconds << " seconds\n";
}

void currentTimeMessageBox(){
    SYSTEMTIME currentTime;
    GetLocalTime(&currentTime);
    char timeString[50];
    sprintf(timeString, "%02d:%02d:%02d",currentTime.wHour, currentTime.wMinute, currentTime.wSecond);

    MessageBox(NULL, timeString, "currentTime", MB_OK);
}

void printNamePC_and_UserPC(){
    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);
    GetComputerName(computerName, &size);

    char userName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD usersize = sizeof(userName);
    GetUserName(userName, &usersize);

    cout << "PC Name: " << computerName << endl;
    cout << "UserName: " << userName << endl;

}


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    printUpTime();
    currentTimeMessageBox();
    printNamePC_and_UserPC();
    return 0;
}