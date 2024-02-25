#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "shell.h"


/**
 * exit_shell - Sets the @shell->exit to 1.
 * @shell: A pointer to the shell_data structure.
 *
 * Note: after each iteration in shel main loop (in start_shell ot handle_pipe)
 * the @shell->exit will be checked. if it is different than 0, shell will be
 * exited
 */
void exit_shell(shell_data *shell)
{
	shell->exit = 1;
}


/**
 * env - Displays the environment variables to @shell->out.
 * @shell: A pointer to the shell_data structure.
 *
 * This function displays the environment, each variable in a line.
 */
void env(shell_data *shell)
{
	char **env_arr, *var;
	int i;

	env_arr = shell->env;
	for (i = 0; env_arr[i] != NULL; i++)
	{
		var = env_arr[i];
		write(fileno(shell->out), var, strlen(var));
		write(fileno(shell->out), "\n", 1);
	}
}

