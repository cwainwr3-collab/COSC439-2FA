#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* Common network constants */
#define ECHOMAX 1024

/* Message formats between OTPA/UA and SA */

typedef enum {
    registerOTPA = 0,
    acknowledgeRegister,
    confirmRegister = acknowledgeRegister,
    login,
    responsePassword,
    responseNewKey,
    logout
} OPTA_UA_MessageType;

#pragma pack(push, 1)
typedef struct {
    uint32_t messageType; /* OPTA_UA_MessageType */
    uint32_t userID;
    uint32_t pubKeyOrEncPwd;
} OPTAorUAtoSA;
#pragma pack(pop)

/* Common globals (used across multiple source files) */
extern int sock;
extern struct sockaddr_in echoServAddr;
extern struct sockaddr_in echoClntAddr;
extern struct sockaddr_in fromAddr;
extern socklen_t cliAddrLen;
extern socklen_t fromSize;

extern int echoServPort;
extern const char *servIP;

extern char echoBuffer[ECHOMAX];
extern char echoString[ECHOMAX];
extern int echoStringLen;
extern int recvMsgSize;
extern int respStringLen;

/* Public API */
int RecieveMessage(int runOnce);
int RegisterOTPA(uint32_t userID, uint32_t publicKey);

/* Utility helpers */
void DieWithError(const char *errorMessage);
void print(const char *message);

#endif /* COMMON_H */
