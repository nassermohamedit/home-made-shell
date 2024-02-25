#ifndef SHELL_H
#define SHELL_H


/**
 * struct shell_data - Data structure for storing shell information.
 * @shname_len: Length of the shell name (@shname).
 * @shname: String containing the name of the shell.
 * @env: Array of strings representing environment variables.
 * @path: Array of strings NULL termincated, representing individual
 * paths in the PATH variable.
 * @prompt_len: Length of the shell prompt (@prompt).
 * @prompt: String containing the shell prompt (i.e. $).
 * @cmds: Number of commands executed by the shell.
 * @in: File pointer to commands input file (i.e. stdin).
 * @out: File pointer to commands output file (i.e. stdout).
 * @err: File pointer for commands errors file (i.e. stderr).
 * @status: Exit status of the last executed command.
 * @exit: Flag indicating whether the shell should exit.
 */
typedef struct shell_data
{
	size_t shname_len;
	char *shname;
	char **env;
	char **path;
	size_t prompt_len;
	char *prompt;
	int cmds;
	FILE *in;
	FILE *out;
	FILE *err;
	int status;
	int exit;
} shell_data;

shell_data *init(char *shname, char **env, char *prompt);
void free_shell(shell_data *shell);
void not_found_message(shell_data *shell, char *fname);
void handle_eof(shell_data *shell);
void print_prompt(shell_data *shell);
void inc_cmd(shell_data *shell);
char **read_command(shell_data *shell);
int run_command(shell_data *shell, char **args);
int handle_pipe(shell_data *shell);
int start_shell(shell_data *shell);
void exit_shell(shell_data *shell);
void env(shell_data *shell);

#endif

