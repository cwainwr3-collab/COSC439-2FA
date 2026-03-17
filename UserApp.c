#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//defining socket for sending to server?
//int sock;

//This method will open a UDP socket and send a specified message (fix arguement for this later) and close once it has recieved a reply
int SendMessage()
{
    /* Create a datagram/UDP socket */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("UA socket() failed");
    printf("UA socket() success\n");

    /* Construct the server address structure */
    echoServAddr.sin_family = AF_INET; /* Internet addr family */
    echoServAddr.sin_addr.s_addr = inet_addr(servIP); /* Server IP address */
    echoServAddr.sin_port = htons(echoServPort); /* Server port */
    /* Send the string to the server */
    if (sendto(sock, echoString, echoStringLen, 0, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) != echoStringLen)
        DieWithError("sendto() sent a different number of bytes than expected");

    /* Recv a response */
    fromSize = sizeof(fromAddr);
    if ((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr *) &fromAddr, &fromSize)) != echoStringLen)
        DieWithError("recvfrom() failed");
    close(sock);
}

//message to SA
typedef struct {

enum { registerOTPA,  acknowledgeRegister, login, responsePassword, responseNewKey, logout} messageType;                                   /* same size as an unsigned int */ 

unsigned int userID;                           /* user identifier */

unsigned int pubKeyOrEncPwd;        /* OTP public key or UA encrypted password */

}OPTAorUAtoSA;

/*  messageType = registerOTPA:
    Message sent from OTPA
    userID = corresponding user’s userID. 
    pubKeyOrEncPwd = 0 (not used)
    messageType = acknowledgeRegister:
    Message sent from an OTPA
    userID = corresponding user’s userID. 
    pubKeyOrEncPwd = 0 (not used)
    messageType = login:
    Message sent from a UA
    userID = corresponding user’s userID. 
    pubKeyOrEncPwd = 0 (not used)
    messageType = responsePassword:
    Message sent from a UA
    userID = corresponding user’s userID. 
    pubKeyOrEncPwd = encrypted password
    messageType = responseNewKey:
    Message sent from an OTPA
    userID = corresponding user’s userID. 
    pubKeyOrEncPwd = OTPA public key
    messageType = logout:
    Message sent from a UA
    userID = corresponding user’s userID. 
    pubKeyOrEncPwd = 0 (not used)
*/