#include "common.h"

//NOT TESTED YET!!!!, IMPLIMENT SOMETHING WITH OPTA IN ORDER TO TEST IF WE HAVE SOCKETS WORKING CORRECTLY BEFORE IMPLIMENTING DHKE OR WHATEVER

// ServerApp listens for messages from OTPA/UA and responds appropriately.
// For this exercise we implement the OTPA registration handshake.
int RecieveMessage(int runOnce)
{
    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("server socket() failed");
    print("server socket() success");

    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET; /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(echoServPort); /* Local port */

    /* Bind to the local address */
    if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("server bind() failed");
    print("server bind() success");

    for (;;) {
        int handled = 0;
        cliAddrLen = sizeof(echoClntAddr); /* Set the size of the in-out parameter */

        /* Block until receive message from a client */
        if ((recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX, 0,
            (struct sockaddr *) &echoClntAddr, &cliAddrLen)) < 0)
            DieWithError("server recvfrom() failed");
        print("server recvfrom() success");

        /* If this is a registration request, respond with confirmRegister */
        if (recvMsgSize == (int)sizeof(OPTAorUAtoSA)) {
            OPTAorUAtoSA req;
            memcpy(&req, echoBuffer, sizeof(req));

            if (req.messageType == registerOTPA) {
                print("server received registerOTPA");

                /* Respond using the same message structure (OPTAorUAtoSA) */
                OPTAorUAtoSA resp = {0};
                resp.messageType = confirmRegister;
                resp.userID = req.userID;
                resp.pubKeyOrEncPwd = 0; /* not used for confirmation */

                if (sendto(sock, &resp, sizeof(resp), 0,
                    (struct sockaddr *) &echoClntAddr, cliAddrLen) != (ssize_t)sizeof(resp))
                    DieWithError("server sendto() failed");

                print("server sent confirmRegister");
                handled = 1;
            }
        }

        /* Default behavior: echo message back */
        if (!handled) {
            if (sendto(sock, echoBuffer, recvMsgSize, 0,
                (struct sockaddr *) &echoClntAddr, cliAddrLen) != recvMsgSize)
                DieWithError("sendto() sent a different number of bytes than expected");
            print("server echo back");
        }

        if (runOnce)
            break;
    }

    close(sock);
    print("server close(sock) success");
    return 0;
}



