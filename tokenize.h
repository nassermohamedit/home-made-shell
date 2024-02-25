#ifndef TOKENIZE_H
#define TOKENIZE_H

int no_tokens(char *string, char *dels, size_t len);
char **tokenize(char *string, char *del, int n);

#endif

