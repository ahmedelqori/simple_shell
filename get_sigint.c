#include "shell.h"

/**
 * get_sigint - Handle the crtl + c call  prompt
 * @sig: represents a signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
