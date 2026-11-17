#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int parse_commands(size_t cmdc, char *cmd[]);

int main(int argc, char *argv[])
{
    fputs("whyshell\n", stdout);

    char *buf = NULL;
    size_t capacity = 0;

    for (;;)
    {
        fputs("whysh? ", stdout);

        if (getline(&buf, &capacity, stdin) == -1)
            break;

        char *cmd[128]; // enforce hard limit of 127 arguments for any command
        size_t cmdc = 0;

        // tokenize input
        char *tok = strtok(buf, " \r\n\t");
        while (tok != NULL && cmdc < 127)
        {
            cmd[cmdc++] = tok;
            tok = strtok(NULL, " \r\n\t");
        }

        cmd[cmdc] = NULL;

        if (cmd[0] == NULL)
            continue;

        if (tok != NULL)
        {
            fputs("Too many arguments!\n", stdout);
            continue;
        }

        /* for (size_t i = 0; i < cmdc; i++) */
        /* { */
        /*     printf("Token index %lu: %s \n", i, cmd[i]); */
        /* } */

        // parse tokenized input token by token
        int parse_code = parse_commands(cmdc, cmd);
        if (parse_code == 1)
            break;
        else if (parse_code == 2)
            continue;
    }

    free(buf);
    return EXIT_SUCCESS;
}

int parse_commands(size_t cmdc, char *cmd[])
{
    if (strcmp(cmd[0], "exit") == 0)
    {
        if (cmdc == 1)
            return 1;
        else
            printf("exit: too many arguments (expected 1, got %lu) \n", cmdc);
    }
    else
    {
        int status;
        pid_t child = fork();
        if (child < 0)
        {
            // forking error
            perror("fork");
            return 2;
        }
        else if (child == 0)
        {
            if (execvp(cmd[0], cmd) == -1)
            {
                // external call call error
                perror("call");
            }
            _exit(127);
        }
        pid_t wait;
        do
        {
            wait = waitpid(child, &status, 0);
        } while (wait == -1 && errno == EINTR);
        if (wait == -1)
            // execution error
            perror("wait");

        return 0;
    }
    return 0;
}
