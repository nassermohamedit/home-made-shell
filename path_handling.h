#ifndef PATH_HANDLING_H
#define PATH_HANDLING_H

char **get_path_array(char *env[]);
int validate_file(char **fname_ptr, char **paths);

#endif

