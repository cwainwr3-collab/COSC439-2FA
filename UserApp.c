#include "common.h"

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
    return 0;
}
