#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include "tokenize.h"
#include "process.h"
#include "path_handling.h"
#include "shell.h"
#include "util.h"


/**
 * init - Initializes the shell_data structure.
 * @shname: The name of the shell.
 * @env: The environment variable array.
 * @prompt: The shell prompt string.
 *
 * This function allocates memory for a shell_data structure,
 * initializes its attributes, and returns a pointer to the created
 * structure. All attributes of the shell are set to default values,
 * or are computed from given arguments.
 *
 * Return: A pointer to the initialized shell_data structure.
 */
shell_data *init(char *shname, char **env, char *prompt)
{
	shell_data *shell = (shell_data *)malloc(sizeof(shell_data));

	shell->shname = shname;
	shell->shname_len = strlen(shname);
	shell->env = env;
	shell->path = get_path_array(env);
	shell->prompt_len = strlen(prompt);
	shell->prompt = prompt;
	shell->cmds = 0;
	shell->status = 0;
	shell->exit = 0;
	shell->in = stdin;
	shell->out = stdout;
	shell->err = stderr;

	return (shell);
}


/**
 * read_command - Reads a command from @shell->in and tokenizes it.
 * @shell: A pointer to the shell_data structure.
 *
 * Note: char **tokenize(char *string, char *del, int n); returns an array
 * of strings args suitable to be passed to execve.
 *
 * Return: An array of NULL terminated strings representing the command and
 * its arguments.
 */
char **read_command(shell_data *shell)
{
	int len, n_tokens;
	char *command, **args;
	size_t size;

	args = NULL;
	command = NULL;
	len = getline(&command, &size, shell->in);
	if (len == -1)
	{
		shell->exit = 1;
		free(command);
		return (args);
	}

	n_tokens = no_tokens(command, " \t\n", len);

	if (n_tokens > 0)
		args = tokenize(command, " \t\n", n_tokens);

	free(command);
	return (args);
}


/**
 * run_command - Executes a command.
 * @shell: A pointer to the shell_data structure.
 * @args: A NULL terminated array of strings containing the command
 * and its arguments.
 *
 * This function executes the specified command using the
 * creat_cmd_process function, checks for the "exit" command, and
 * handles cases where the command is not found.
 *
 * Return: Always returns 0.
 */
int run_command(shell_data *shell, char **args)
{
	inc_cmd(shell);

	if (args == NULL)
		return (0);

	if (strcmp(args[0], "exit") == 0)
	{
		exit_shell(shell);
		return (0);
	}

	if (strcmp(args[0], "env") == 0)
	{
		env(shell);
		return (0);
	}

	if (validate_file(&args[0], shell->path) == -1)
	{
		shell->status = 127;
		not_found_message(shell, args[0]);
	}
	else
	{
		creat_cmd_process(args, shell->env);
		wait(&shell->status);
		return (0);
	}
	return (0);
}


/**
 * handle_pipe - Handles the shell operation in a non interactive mode.
 * @shell: A pointer to the shell_data structure.
 *
 * This functiom reads and executes commands in a non interactive mode
 * until the exit flag is set.
 *
 * Return: The exit status of the last executed command.
 */
int handle_pipe(shell_data *shell)
{
	char **args;

	while (!shell->exit)
	{
		args = read_command(shell);
		run_command(shell, args);
		free_2d_arr((void **) args, -1);
	}
	return (shell->status);
}


/**
 * start_shell - Handles the interactive mode of the shell.
 * @shell: A pointer to the shell_data structure.
 *
 * This function enters an while loop, it prints the prompt, reads
 * and run user commands until @shell->exit is different than 0.
 *
 * Return: The exit status of the last executed command.
 */
int start_shell(shell_data *shell)
{
	char **args;

	args = NULL;
	if (!isatty(fileno(stdin)))
		return (handle_pipe(shell));

	while (!shell->exit)
	{
		print_prompt(shell);
		args = read_command(shell);

		run_command(shell, args);

		free_2d_arr((void **) args, -1);
	}
	return (shell->status);
}

