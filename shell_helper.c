#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "shell.h"
#include "util.h"



/**
 * free_shell - Frees the memory allocated for a shell_data structure.
 * @shell: A pointer to the shell_data structure to be freed.
 */
void free_shell(shell_data *shell)
{
	free_2d_arr((void **)shell->path, -1);
	free(shell);
}


/**
 * not_found_message - Prints a "not found" error message to @shell->err.
 * @shell: A pointer to the shell_data structure.
 * @fname: The name of the command/file that was not found.
 */
void not_found_message(shell_data *shell, char *fname)
{
	char buffer[200];
	int len;

	sprintf(buffer, "%s: %d: %s: not found\n", shell->shname, shell->cmds, fname);
	len = strlen(buffer);
	write(fileno(shell->err), buffer, len);
}


/**
 * handle_eof - Handles the end-of-file condition by writing a newline.
 * to @shell->out
 * @shell: A pointer to the shell_data structure.
 */
void handle_eof(shell_data *shell)
{
	write(fileno(shell->out), "\n", 1);
}


/**
 * inc_cmd - Increments the command counter in the shell_data structure
 * each time a command is run.
 * @shell: A pointer to the shell_data structure.
 */
void inc_cmd(shell_data *shell)
{
	shell->cmds++;
}


/**
 * print_prompt - Prints the shell prompt specified by @shell->prompt
 * to @shell->out.
 * @shell: A pointer to the shell_data structure.
 */
void print_prompt(shell_data *shell)
{
	write(fileno(shell->out), shell->prompt, shell->prompt_len);
}

