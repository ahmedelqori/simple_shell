#include "shell.h"

/**
 * _memcpy - Copies data from source to destination pointers.
 * @newptr: represents pointer to the destination. 
 * @ptr: represents pointer to source. 
 * @size: represents the size of the new pointer. 
 *
 * Return: nothing to return.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * _realloc - reallocates memory block. 
 * @ptr: pointer to previously allocated memory. 
 * @old_size: size in (in bytes) of the allocated memory space for ptr.
 * @new_size: new size (in bytes) of the  memory block.
 *
 * Return: pointer to memory block. 
 * Returns ptr if new_size == old_size,
 * NULL if malloc fails
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocdpr - reallocates  memory block of double pointer.
 * @ptr: double pointer to previously allocated memory. 
 * @old_size: size (in bytes) of allocated memory space of ptr.
 * @new_size: new size ( in bytes) of memory block.
 *
 * Return: pointer to memory block
 * Return ptr if new_size == old_size,
 * NULL if malloc fails. 
 */
char **_reallocdpr(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
