#include "main.h"

/**
 * set_bit - A fun that sets a bit at a given index to 1
 * @n: A pointer pointer to the no to change
 * @index: index of the bit to set to 1
 *
 * Return: 1 for success, -1 for failure
 */
int set_bit(unsigned long int *n, unsigned int index)
{
	if (index > 63)
		return (-1);

	*n = ((1UL << index) | *n);
	return (1);
}
