#include "config.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    printf("Aloha! from %s in %s v%s\n", argv[0], PROJECT_NAME, PROJECT_VERSION);
    return EXIT_SUCCESS;
}
