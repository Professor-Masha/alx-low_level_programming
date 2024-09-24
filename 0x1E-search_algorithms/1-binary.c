#include <stdio.h>
#include "search_algos.h"

/**
 * print_array - Helper function to print the array.
 * @array: Pointer to the first element of the array.
 * @start: Starting index of the subarray.
 * @end: Ending index of the subarray.
 *
 * Return: void
 */
void print_array(int *array, size_t start, size_t end)
{
	size_t i;

	printf("Searching in array: ");
	for (i = start; i < end; i++)
	{
		if (i != start)
			printf(", ");
		printf("%d", array[i]);
	}
	printf("\n");
}

/**
 * binary_search - Searches for a value in a sorted array using binary search.
 * @array: Pointer to the first element of the array to search.
 * @size: The number of elements in the array.
 * @value: The value to search for.
 *
 * Return: The index where value is located, or -1 if not found or
 *         if array is NULL.
 */
int binary_search(int *array, size_t size, int value)
{
	size_t left = 0, right = size - 1, mid;

	if (array == NULL)  /* Check if array is NULL */
		return (-1);

	while (left <= right)  /* Continue searching */
	{
		mid = left + (right - left) / 2;  /* Calculate mid index */
		print_array(array, left, right + 1);  /* Print the array searched */

		if (array[mid] == value)  /* Check if mid element is the value */
			return (mid);  /* Return mid index if found */
		else if (array[mid] < value)  /* If value is greater, ignore left half */
			left = mid + 1;
		else  /* If value is smaller, ignore right half */
			right = mid - 1;
	}

	return (-1);  /* Return -1 if value not found */
}
