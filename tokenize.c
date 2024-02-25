#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 * no_tokens - Counts the number of tokens in a string using specified
 * delimiters.
 * @string: The input string.
 * @dels: A string containing delimiter characters.
 * @len: The length of the input string.
 *
 * This function counts the number of tokens in the input string using
 * the specified delimiter characters. Tokens are defined as sequences
 * of characters that are not in the delimiter string. This function is
 * to be used to convert a command represented by a string into and array
 * of strings args.
 *
 * Return: The number of tokens in the input string.
 */
int no_tokens(char *string, char *dels, size_t len)
{
	int count, i;
	char prev;

	if (len == 0)
		return (0);

	prev = dels[0];
	count = 0;
	for (i = 0; i < (int) len; i++)
	{
		char c = string[i];
	if (strchr(dels, c) == NULL && strchr(dels, prev) != NULL)
		count++;
	prev = c;
	}
	return (count);
}


/**
 * tokenize - Tokenizes a string into an array of strings using specified
 * delimiters.
 * @string: The input string to be tokenized.
 * @del: A string containing delimiter characters.
 * @n: Number of tokens. It should be less or equal to the number of tokens
 * in @string.
 *
 * This function tokenizes the input string into an array of strings using
 * the specified delimiter characters. The number of expected tokens is
 * provided as an argument. The resulting array of strings is terminated
 * with a NULL pointer.
 *
 * Return: A NULL terminated array of strings representing the tokens in the
 * input string.
 */
char **tokenize(char *string, char *del, int n)
{
	char **tokens = (char **)malloc((n + 1) * sizeof(char *));
	char *token = strtok(string, del);
	int token_len = strlen(token);
	int i;

	tokens[0] = (char *)malloc((token_len + 1) * sizeof(char));
	strcpy(tokens[0], token);
	for (i = 1; i < n; i++)
	{
		token = strtok(NULL, del);
		token_len = strlen(token);
		tokens[i] = (char *)malloc((token_len + 1) * sizeof(char));
		strcpy(tokens[i], token);
	}
	tokens[n] = NULL;
	return (tokens);
}
