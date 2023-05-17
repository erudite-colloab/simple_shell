#include "shell.h"

/**
 * bfree - pointer to free and the address to NULL
 * @ptr: pointer's address to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
