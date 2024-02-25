#include<stdlib.h>
#include "util.h"


/**
 * free_2d_arr - Frees memory allocated for a two-dimensional array.
 * @arr: A pointer to the two-dimensional array.
 * @n: The number of elements to free (or -1 for the entire array).
 */
void free_2d_arr(void **arr, int n)
{
	int i;

	if (arr == NULL)
		return;

	for (i = 0; (n == -1 && arr[i] != NULL) || i < n; i++)
		free(arr[i]);
	free(arr);
}
