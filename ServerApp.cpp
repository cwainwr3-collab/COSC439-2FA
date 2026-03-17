
//NOT TESTED YET!!!!, IMPLIMENT SOMETHING WITH OPTA IN ORDER TO TEST IF WE HAVE SOCKETS WORKING CORRECTLY BEFORE IMPLIMENTING DHKE OR WHATEVER

//This method will open UDP socket for the serverApp so that it can recieve messages
int RecieveMessage()
{
    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("server socket() failed");
    print("server socket() success");

    /* Construct local address structure */
    echoServAddr.sin_family = AF_INET; /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(echoServPort); /* Local port */

    /* Bind to the local address */
    if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("server bind() failed");
    print("server bind() success");

    for (;;) /* Run forever */
    {   
        cliAddrLen = sizeof(echoClntAddr); /* Set the size of the in-out parameter */
            
        /* Block until receive message from a client */
        if ((recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX, 0,
            (struct sockaddr *) &echoClntAddr, &cliAddrLen)) < 0)
            DieWithError("server recvfrom() failed");
        print("server recvfrom() success");

        /* Send received datagram back to the client */
        if (sendto(sock, echoBuffer, recvMsgSize, 0, (struct sockaddr *) &echoClntAddr, sizeof(echoClntAddr)) != recvMsgSize)
            DieWithError("sendto() sent a different number of bytes than expected");
        print("sever sendto() success");
    }
    close(sock);
    print("server close(sock) success");
}

typedef struct {

enum { confirmRegister, requestNewKey  } messageType;                                  /* same as unsigned int */ 

unsigned int userID;                           /* user identifier*/

unsigned int publicKey;                      /* OTP public key */
} SAtoOTPA;

/*  messageType = confirmRegister
    userID = corresponding user’s userID. 
    publicKey = 0 (not used)
    messageType = requestNewKey
    userID = corresponding user’s userID. 
    publicKey = SA public key
*/

typedef struct {

enum { requestPassword,  confirmLogin  } messageType;          /* same size as an unsigned int */

unsigned int userID;                           /* user identifier */

enum { success, fail} status;                                 /* login status */        

} SAtoUA;

/*  messageType = requestPassword:
    userID = corresponding user’s userID. 
    status = (not used)
    messageType = confirmLogin:
    userID = corresponding user’s userID. 
    status = login status
*/