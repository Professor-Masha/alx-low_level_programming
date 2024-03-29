#ifndef LISTS_H
#define LISTS_H

/**
 * struct list_s - a singly linked list.
 * @str: string - a malloc string.
 * @len: length of string.
 * @next: points to the next node.
 *
 * Description: C - Singly linked lists
 * for Holberton project
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

list_t *add_node(list_t **head, const char *str);
list_t *add_node_end(list_t **head, const char *str);
size_t print_list(const list_t *h);
size_t list_len(const list_t *h);
void free_list(list_t *head);

#endif
