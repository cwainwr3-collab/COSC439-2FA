#include "common.h"

/* Shared globals */
int sock = -1;
struct sockaddr_in echoServAddr;
struct sockaddr_in echoClntAddr;
struct sockaddr_in fromAddr;
socklen_t cliAddrLen;
socklen_t fromSize;

int echoServPort = 7; /* default echo port (can be overridden) */
const char *servIP = "127.0.0.1"; /* default server IP */

char echoBuffer[ECHOMAX];
char echoString[ECHOMAX];
int echoStringLen = 0;
int recvMsgSize = 0;
int respStringLen = 0;

void DieWithError(const char *errorMessage)
{
    perror(errorMessage);
    exit(EXIT_FAILURE);
}

void print(const char *message)
{
    if (message != NULL)
        printf("%s\n", message);
}
