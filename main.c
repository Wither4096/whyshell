#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char buf[4096];
	fputs("whyshell\n", stdout);
	for (;;) {
		fputs("whysh> ", stdout);
		fgets(buf, sizeof(buf), stdin);
		if(strcmp(buf, "exit\n") == 0)
			break;
	}
	return EXIT_SUCCESS;
}
