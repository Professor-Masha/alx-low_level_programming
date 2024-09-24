#include <stdio.h>
#include <stdlib.h>
#include "search_algos.h"

/**
 * create_list - Creates a singly linked list from an array of integers.
 * @array: The array of integers.
 * @size: The size of the array.
 *
 * Return: A pointer to the head of the created list.
 */
listint_t *create_list(int *array, size_t size)
{
    listint_t *head = NULL, *node = NULL, *new = NULL;
    size_t i;

    for (i = 0; i < size; i++)
    {
        new = malloc(sizeof(listint_t));
        if (new == NULL)
            return (NULL);
        new->n = array[i];
        new->index = i;
        new->next = NULL;

        if (head == NULL)
            head = new;
        else
            node->next = new;
        node = new;
    }

    return (head);
}

/**
 * print_list - Prints the elements of a singly linked list.
 * @list: A pointer to the head of the list to print.
 */
void print_list(const listint_t *list)
{
    while (list != NULL)
    {
        printf("Index[%lu] = [%d]\n", list->index, list->n);
        list = list->next;
    }
}

/**
 * free_list - Frees a singly linked list.
 * @list: A pointer to the head of the list to free.
 */
void free_list(listint_t *list)
{
    listint_t *temp;

    while (list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp);
    }
}

