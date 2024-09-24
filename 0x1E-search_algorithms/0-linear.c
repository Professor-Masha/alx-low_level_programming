#include <stdio.h>
#include "search_algos.h"

/**
 * linear_search - Searches for a value in an array of integers.
 * @array: Pointer to the first element of the array to search in.
 * @size: The number of elements in the array.
 * @value: The value to search for.
 *
 * Return: The first index where value is located, or -1 if not found
 *         or if array is NULL.
 */
int linear_search(int *array, size_t size, int value)
{
	size_t i;

	if (array == NULL) /* Check if array is NULL */
		return (-1);

	for (i = 0; i < size; i++) /* Iterate through each element */
	{
		printf("Value checked array[%lu] = [%d]\n", (unsigned long)i, array[i]);
		if (array[i] == value) /* Check if current element is value */
			return (i); /* Return index if found */
	}

	return (-1); /* Return -1 if value not found */
}

