#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <limits.h>
#include "tokenize.h"
#include "util.h"
#include "path_handling.h"


/**
 * get_path_string - Extracts and returns the value of the PATH  in the env
 * variable.
 *
 * @env: The environment variable array, same as that given to the main
 * function.
 *
 * Return: A string containing paths value part of the PATH key in env.
 */
char *get_path_string(char **env)
{
	int i;

	i = 0;
	for (i = 0; env[i] != NULL; i++)
	{
		if (strncmp(env[i], "PATH", 4) == 0)
			return (env[i] + 5);
	}
	return (NULL);
}

/**
 * get_path_array - Extracts individual paths from the PATH environment
 * variable.
 *
 * @env: The environment variable array, same as that given to the main
 * function.
 *
 * Return: An array of strings containing individual paths terminated
 * by a NULL.
 */
char **get_path_array(char *env[])
{
	char **paths, *path, *path_cpy, *token;
	int i, no_paths;

	path = get_path_string(env);
	if (path == NULL)
		return (NULL);
	no_paths = no_tokens(path, ":", strlen(path));
	if (no_paths == 0)
		return (NULL);
	path_cpy = (char *)malloc((strlen(path) + 1) * sizeof(char));
	strcpy(path_cpy, path);
	paths = (char **)malloc((no_paths + 1) * sizeof(char *));
	token = strtok(path_cpy, ":");
	i = 0;
	while (token != NULL)
	{
		paths[i] = (char *)malloc((strlen(token) + 1) * sizeof(char));
		if (!paths[i])
		{
			free(path_cpy);
			free_2d_arr((void **)paths, no_paths + 1);
			return (NULL);
		}
		strcpy(paths[i], token);
		i++;
		token = strtok(NULL, ":");
	}
	paths[no_paths] = NULL;
	free(path_cpy);
	return (paths);
}


/**
 * validate_file - Validates the existence of a file in the given paths.
 * @fname_ptr: A pointer to the file name (may be modified).
 * @paths: An array of strings containing individual paths.
 *
 * Return: 0 if the file is found, -1 otherwise.
 */
int validate_file(char **fname_ptr, char **paths)
{
	char *file_name;
	int i;

	file_name = *fname_ptr;
	if (file_name[0] == '/' && access(file_name, F_OK) == 0)
		return (0);
	if (file_name[0] == '/')
		return (-1);
	if (file_name[0] == '.')
	{
		char *real_path = realpath(file_name, NULL);

		if (real_path != NULL)
		{
			free(file_name);
			*fname_ptr = real_path;
			return (0);
		}
		return (-1);
	}
	if (paths == NULL)
		return (-1);
	for (i = 0; paths[i] != NULL; i++)
	{
		int new_len = strlen(paths[i]) + strlen(file_name) + 2;
		char *absolute_path = (char *)malloc(new_len * sizeof(char));

		if (absolute_path == NULL)
			exit(1);
		sprintf(absolute_path, "%s/%s", paths[i], file_name);
		if (access(absolute_path, F_OK) != -1)
		{
			*fname_ptr = absolute_path;
			free(file_name);
			return (0);
		}
		free(absolute_path);
	}
	return (-1);
}

