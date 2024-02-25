#include<stdio.h>
#include<stdlib.h>
#include <stdio.h>
#include "shell.h"


/**
 * main - Entry point for the shell program.
 * @ac: The number of command-line arguments passed to the program.
 * @args: An array of strings containing command-line arguments.
 * @env: The environment variable array.
 *
 * The main function should initialize the shell data structure,
 * and start it by running the function start_shell(). when start_shell
 * returns, memory of @shell is freed and returned value of start_shell
 * is returned.
 *
 * Return: The exit status of the shell program.
 */
int main(int ac, char **args, char **env)
{
	shell_data *shell;
	char *prompt;
	int result;

	prompt = "$ ";
	shell = init(args[0], env, prompt);

	if (ac > 1)
		perror("");

	result = start_shell(shell);
	free_shell(shell);
	return (result);
}

