#include <stdio.h>
#include <time.h>

#include <windows.h>

#define OP_CUSTOM (1 <<  0)
#define OP_SILENT (1 << 31)

static int      operation = 0;
static char     datetime[32] = { 0 };
static char*    argv_0;

_Noreturn void __usage_error(char* msg)
{
    fprintf(stderr,
        "Error message: %s.\n"
        "\n"
        "Usage: \n"
        "  %s <path/to/file> [path/to/other/files] [ <optional arguments> ]\n"
        "\n"
        "positional arguments:\n"
        "  path/to/payload\n"
        "\n"
        "optional arguments:\n"
        "  -c\t\tuse custom datetime string for the files\n"
        "    \t\tformat: YYYYMMDDHHMMSS\n"
        "  -s,--silent\tsuppress the standard output\n"
        "\n"
        "example:\n"
        "  %s test.txt -c \"19990101000000\"\n"
        , msg, argv_0, argv_0);
    exit(-1);
}

char* parse_command_line(int argc, char** argv)
{
    char buffer[32] = { 0 };

    if (argc < 2)
    {
        __usage_error("No arguments supplied");
    }

    for (int i = 1; i < argc; i++)
    {
        switch (argv[i][0])
        {
            case '-':
            {
                switch (argv[i][1])
                {
                    case 'c':
                    {
                        if (i+1 >= argc)
                        {
                            __usage_error("No format specified");
                        }
                        else
                        {
                            operation |= OP_CUSTOM;
                            memcpy(datetime, argv[i+1], sizeof("YYYYMMDDHHMMSS"));
                        }

                        break;
                    }
                    case 's':
                    {
                        operation |= OP_SILENT;
                        break;
                    }
                    case '-':
                    {
                        snprintf(buffer, sizeof(buffer), "%s", argv[i]+2);
                        if (!strncmp("silent", buffer, sizeof("silent")))
                        {
                            operation |= OP_SILENT;
                        }
                        else if (!strncmp("custom", buffer, sizeof("custom")))
                        {
                            if (i+1 >= argc)
                            {
                                __usage_error("No format specified");
                            }
                            else
                            {
                                operation |= OP_CUSTOM;
                                memcpy(datetime, argv[i+1], sizeof("YYYYMMDDHHMMSS"));
                            }
                        }
                        else
                        {
                            __usage_error("unknown option supplied");
                        }
                        break;
                    }
                    default:
                    {
                        __usage_error("unknown option supplied");
                    }
                }
            }
        }
    }

    return datetime;
}

void SetDefaultTime(LPSYSTEMTIME pSystemTime)
{
    GetLocalTime(pSystemTime);
    pSystemTime->wYear         = 1999;
    pSystemTime->wMonth        = 12;
    pSystemTime->wDay          = 31;
    pSystemTime->wDayOfWeek    = 5;
    pSystemTime->wHour         = 0;
    pSystemTime->wMinute       = 0;
    pSystemTime->wSecond       = 0;
    pSystemTime->wMilliseconds = 0;
}

void SetCustomTime(LPSYSTEMTIME pSystemTime, LPCSTR fmt)
{
    if (strlen(fmt) != 14)
    {
        __usage_error("Invalid datetime format");
    }

    for (int i = 0; i < 14; i++)
    {
        if ((fmt[i] < '0') || (fmt[i] > '9'))
        {
            __usage_error("Invalid character detected");
        }
    }

    char buffer_wYear[5]   = { 0 };
    char buffer_wMonth[3]  = { 0 };
    char buffer_wDay[3]    = { 0 };
    char buffer_wHour[3]   = { 0 };
    char buffer_wMinute[3] = { 0 };
    char buffer_wSecond[3] = { 0 };

    memcpy(buffer_wYear,   fmt+0,  sizeof(buffer_wYear)-1);
    memcpy(buffer_wMonth,  fmt+4,  sizeof(buffer_wMonth)-1);
    memcpy(buffer_wDay,    fmt+6,  sizeof(buffer_wDay)-1);
    memcpy(buffer_wHour,   fmt+8,  sizeof(buffer_wHour)-1);
    memcpy(buffer_wMinute, fmt+10, sizeof(buffer_wMinute)-1);
    memcpy(buffer_wSecond, fmt+12, sizeof(buffer_wSecond)-1);

    sscanf(buffer_wYear,   "%hu", &(pSystemTime->wYear));
    sscanf(buffer_wMonth,  "%hu", &(pSystemTime->wMonth));
    sscanf(buffer_wDay,    "%hu", &(pSystemTime->wDay));
    sscanf(buffer_wHour,   "%hu", &(pSystemTime->wHour));
    sscanf(buffer_wMinute, "%hu", &(pSystemTime->wMinute));
    sscanf(buffer_wSecond, "%hu", &(pSystemTime->wSecond));
    sscanf(buffer_wYear,   "%hu", &(pSystemTime->wYear));
}

int main(int argc, char** argv)
{
    FILE*       fp;
    HANDLE      hFile;
    SYSTEMTIME  system_time;
    FILETIME    file_time;
    LPCSTR      file_name;

    argv_0 = argv[0];
    parse_command_line(argc, argv);

    for (int i = 1; i < argc; i++)
    {
        // Make sure the file exists
        file_name = argv[i];
        if (!(fp = fopen(file_name, "rb")))
        {
            continue;
        }
        else
        {
            fclose(fp);
        }

        if (operation & 1)
        {
            SetCustomTime(&system_time, datetime);
        }
        else
        {
            SetDefaultTime(&system_time);
        }

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

        char* _datetime = datetime[0] ? datetime : "default";
        if ((operation >> 31) & 1)
        {
            fprintf(stdout, "'%s' successfully processed to date-time: %s", argv[i], _datetime);
        }
    }

    return 0;
}
