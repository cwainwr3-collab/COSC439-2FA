#include "common.h"

int main(int argc, char **argv)
{
    /* Allow overriding the listening port for quick local tests */
    if (argc > 1) {
        echoServPort = atoi(argv[1]);
    }

    printf("Server listening on port %d\n", echoServPort);
    return RecieveMessage(1);
}
