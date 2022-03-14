#include <stdio.h>
#include <time.h>

#include <windows.h>

#define OP_CUSTOM (1 <<  0)
#define OP_SILENT (1 << 31)

_Noreturn void __usage_error(char* msg, char* argv_0)
{
    fprintf(stderr,
        "Error message: %s.\n"
        "\n"
        "Usage: %s <path/to/file> [path/to/other/files] [ <optional arguments> ]\n"
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
        "  %s test.txt -c \"19990101000000\""
        , msg, argv_0, argv_0);
    exit(-1);
}

int parse_command_line(int argc, char** argv)
{
    int operation = 0;
    char buffer[32];

    if (argc < 2)
    {
        __usage_error(argv[0], "No arguments supplied");
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
                    case 'C':
                    {
                        operation |= OP_CUSTOM;
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
                            operation |= OP_CUSTOM;
                        }
                        else
                        {
                            __usage_error(argv[0], "unknown option supplied");
                        }
                        break;
                    }
                }
            }
        }
    }

    return operation;
}

int main(int argc, char** argv)
{
    FILE*       fp;
    HANDLE      hFile;
    SYSTEMTIME  system_time;
    FILETIME    file_time;
    LPCSTR      file_name;
    LPCSTR      datetime;
    BOOL        operation;

    operation = parse_command_line(argc, argv);

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

        GetLocalTime(&system_time);

        system_time.wYear         = 1999;
        system_time.wMonth        = 12;
        system_time.wDay          = 31;
        system_time.wDayOfWeek    = 5;
        system_time.wMilliseconds = 0;
        system_time.wMinute       = 0;
        system_time.wHour         = 0;
        system_time.wSecond       = 0;

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

        datetime = datetime ? datetime : "default";
        if (!(operation & OP_SILENT))
        {
            fprintf(stdout, "'%s' successfully processed to date-time: %s", argv[i], datetime);
        }
    }
    

    return 0;
}
