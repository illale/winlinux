#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#define BUFFERSIZE 1024

int main( int argc, char *argv[] ) {
    WIN32_FIND_DATA ffd;
    LARGE_INTEGER filesize;
    TCHAR szDIR[MAX_PATH];
    size_t length_or_arg;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError=0;

    if (argc == 1) {
        printf("Usage: ls [directory]");
        return 2;
    }

    StringCchLength(argv[1], MAX_PATH, &length_or_arg);

    if (length_or_arg > (MAX_PATH - 3)) {
        printf("Path is too long \n");
        return 2;
    }

    StringCchCopy(szDIR, MAX_PATH, argv[1]);
    StringCchCat(szDIR, MAX_PATH, TEXT("\\*"));

    hFind = FindFirstFile(szDIR, &ffd);

    if (INVALID_HANDLE_VALUE == hFind) {
        printf("Error");
        return dwError;
    }

    do {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            printf("\t%s\t%ld bytes\n", ffd.cFileName, filesize.QuadPart);
        } else {
            filesize.LowPart = ffd.nFileSizeLow;
            filesize.HighPart = ffd.nFileSizeHigh;
            printf("\t%s\t%ld bytes\n", ffd.cFileName, filesize.QuadPart);
        }
    } while(FindNextFile(hFind, &ffd) != 0);

    dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES) {
        printf("No more files");
    }

    FindClose(hFind);
    return dwError;

}