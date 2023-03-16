#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void tcp()

int main(int argc, char *argv[]) {
    int opt;
    char *host = NULL;
    int port = 0;
    char *mode = NULL;

    // parsing arguments from command line
    while ((opt = getopt(argc, argv, "h:p:m:")) != -1) {
        switch (opt) {
            case 'h':
                host = optarg;
                break;
            case 'p':
                port = atoi(optarg);
                break;
            case 'm':
                mode = optarg;
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s -h host -p port -m mode\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (host == NULL || port == 0 || mode == NULL) {
        fprintf(stderr, "Usage: %s -h host -p port -m mode\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("host=%s, port=%d, mode=%s\n", host, port, mode);

    return 0;
}
