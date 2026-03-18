#include "common.h"

// Register this OTPA with the ServerApp by sending a "registerOTPA" message and
// waiting for the server to reply with "acknowledgeRegister".
//
// Returns 0 on success, or -1 on failure.
int RegisterOTPA(uint32_t userID, uint32_t publicKey)
{
    OPTAorUAtoSA request = {0};
    request.messageType = registerOTPA;
    request.userID = userID;
    request.pubKeyOrEncPwd = publicKey;

    /* Create a datagram/UDP socket */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("OPTA socket() failed");

    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);
    echoServAddr.sin_port = htons(echoServPort);

    /* Send registration request */
    if (sendto(sock, &request, sizeof(request), 0,
               (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) != (ssize_t)sizeof(request)) {
        DieWithError("OPTA sendto() failed");
    }

    /* Wait for server acknowledgement */
    fromSize = sizeof(fromAddr);
    OPTAorUAtoSA response = {0};
    ssize_t recvLen = recvfrom(sock, &response, sizeof(response), 0,
                               (struct sockaddr *)&fromAddr, &fromSize);
    if (recvLen != (ssize_t)sizeof(response)) {
        DieWithError("OPTA recvfrom() failed");
    }

    close(sock);

    if (response.messageType != confirmRegister || response.userID != userID) {
        return -1;
    }

    return 0;
}
