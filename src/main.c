#include <stdio.h>

#include <windows.h>

int main(int argc, char** argv)
{
    FILE*  fp;
    HANDLE hFile;
    LPCSTR file_name;

    // make sure there is an argument or else end program
    if (argc != 2)
    {
        return -1;
    }
    
    // make sure the argument exists
    file_name = argv[1];
    if (!(fp = fopen(file_name, "rb")))
    {
        return -1;
    }
    else
    {
        fclose(fp);
    }

    SYSTEMTIME system_time;
    GetSystemTime(&system_time);

    system_time.wYear         = 1979;
    system_time.wMonth        = 1;
    system_time.wDay          = 1;
    system_time.wDayOfWeek    = 1;
    system_time.wMilliseconds = 0;
    system_time.wMinute       = 0;
    system_time.wHour         = 0;
    system_time.wSecond       = 0;

    FILETIME file_time;
    SystemTimeToFileTime(&system_time, &file_time);

    hFile = CreateFile(file_name,                          // File name
                       FILE_WRITE_ATTRIBUTES,              // Desired access
                       FILE_SHARE_READ | FILE_SHARE_WRITE, // Share mode
                       NULL,                               // Security Attributes
                       OPEN_EXISTING,                      // Creation disposition
                       FILE_ATTRIBUTE_NORMAL,              // Creation flags
                       NULL);                              // Template file

    SetFileTime(hFile, &file_time, &file_time, &file_time);
    CloseHandle(hFile);

    return 0;
}
