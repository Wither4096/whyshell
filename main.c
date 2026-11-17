#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *buf = NULL;
    size_t capacity = 0;

    fputs("whyshell\n", stdout);
    for (;;)
    {
        fputs("whysh? ", stdout);

        if (getline(&buf, &capacity, stdin) == -1)
            break;

        if (strcmp(buf, "exit\n") == 0)
            break;
    }

    free(buf);
    return EXIT_SUCCESS;
}
