#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "process.h"


/**
 * creat_cmd_process - Creates a child process to execute a command.
 * @cmd: An array of strings representing the command and its arguments.
 *
 * @env: The environment variable array.
 *
 * This function creates a new process using fork() and executes the
 * specified command in the child process using execve.
 * If the fork or execve system calls encounter an error, the function
 * returns -1, otherwise, it returns the pid of the child process
 * Return: The process ID (PID) of the child process.
 */
pid_t creat_cmd_process(char **cmd, char **env)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		exit(1);
	}

	if (pid == 0)
	{
		execve(cmd[0], cmd, env);
		exit(1);
	}

	return (pid);
}
