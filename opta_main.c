#include "common.h"
#include <inttypes.h>

int main(int argc, char **argv)
{
    uint32_t userID = 1;
    uint32_t publicKey = 0x12345678;

    if (argc > 1) {
        userID = (uint32_t)atoi(argv[1]);
    }
    if (argc > 2) {
        publicKey = (uint32_t)strtoul(argv[2], NULL, 0);
    }
    if (argc > 3) {
        echoServPort = atoi(argv[3]);
    }

    printf("OPTA registering userID=%" PRIu32 " publicKey=0x%08" PRIx32 " to port %d\n", userID, publicKey, echoServPort);
    int result = RegisterOTPA(userID, publicKey);
    printf("OPTA registration %s\n", result == 0 ? "succeeded" : "failed");
    return result != 0;
}
