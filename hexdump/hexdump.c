#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define BUFFERSIZE 1024

int main( int argc, char *argv[] ) {
    FILE *fptr;
    int errnum;
    char *buffer;
    buffer = malloc(BUFFERSIZE);
    

    if (argc == 1) {
        printf("Usage: hexdump [filename]\n");
        return 1;
    }

    fptr = fopen(argv[1], "rb");

    if (fptr == NULL) {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error");

    } else {
        printf("----------------\n");
        while( fgets(buffer, 255, (FILE*)fptr) != NULL ) {
            for (int i = 0; i < strlen(buffer); i++) {
                printf("%02x ", (unsigned int) buffer[i]);
            }
            printf("| ");
            printf("%s", buffer);
            printf("\n");
        }
        printf("\n----------------\n");
    }

    fclose(fptr);
    return 0;
}