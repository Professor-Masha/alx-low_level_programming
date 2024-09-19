#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * struct shash_node_s - Node of a sorted hash table
 *
 * @key: The key, string
 * The key is unique in the HashTable
 * @value: The value corresponding to a key
 * @next: A pointer to the next node of the List
 * @sprev: A pointer to the previous element of the sorted linked list
 * @snext: A pointer to the next element of the sorted linked list
 */
typedef struct shash_node_s
{
    char *key;
    char *value;
    struct shash_node_s *next;
    struct shash_node_s *sprev;
    struct shash_node_s *snext;
} shash_node_t;

/**
 * struct shash_table_s - Sorted hash table data structure
 *
 * @size: The size of the array
 * @array: An array of size @size
 * Each cell of this array is a pointer to the first node of a linked list
 * @shead: A pointer to the first element of the sorted linked list
 * @stail: A pointer to the last element of the sorted linked list
 */
typedef struct shash_table_s
{
    unsigned long int size;
    shash_node_t **array;
    shash_node_t *shead;
    shash_node_t *stail;
} shash_table_t;

/* Function prototypes */
shash_table_t *shash_table_create(unsigned long int size);
int shash_table_set(shash_table_t *ht, const char *key, const char *value);
char *shash_table_get(const shash_table_t *ht, const char *key);
void shash_table_print(const shash_table_t *ht);
void shash_table_print_rev(const shash_table_t *ht);
void shash_table_delete(shash_table_t *ht);
unsigned long int key_index(const unsigned char *key, unsigned long int size);

/**
 * shash_table_create - Creates a sorted hash table
 * @size: The size of the hash table
 *
 * Return: A pointer to the new hash table, or NULL on failure
 */
shash_table_t *shash_table_create(unsigned long int size)
{
    shash_table_t *new_table;
    unsigned long int i;

    new_table = malloc(sizeof(shash_table_t));
    if (new_table == NULL)
        return (NULL);

    new_table->size = size;
    new_table->array = malloc(sizeof(shash_node_t *) * size);
    if (new_table->array == NULL)
    {
        free(new_table);
        return (NULL);
    }

    for (i = 0; i < size; i++)
        new_table->array[i] = NULL;

    new_table->shead = NULL;
    new_table->stail = NULL;

    return (new_table);
}

/**
 * shash_table_set - Adds or updates a key-value pair in the sorted hash table
 * @ht: The hash table
 * @key: The key
 * @value: The value
 *
 * Return: 1 on success, 0 on failure
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
    unsigned long int index;
    shash_node_t *new_node, *current;

    if (ht == NULL || key == NULL || value == NULL)
        return (0);

    index = key_index((const unsigned char *)key, ht->size);
    current = ht->array[index];

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = strdup(value);
            return (1);
        }
        current = current->next;
    }

    new_node = malloc(sizeof(shash_node_t));
    if (new_node == NULL)
        return (0);

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = ht->array[index];
    ht->array[index] = new_node;

    // Insert into the sorted linked list
    shash_node_t *prev = NULL, *sorted_current = ht->shead;
    while (sorted_current != NULL && strcmp(sorted_current->key, key) < 0)
    {
        prev = sorted_current;
        sorted_current = sorted_current->snext;
    }

    new_node->sprev = prev;
    new_node->snext = sorted_current;

    if (prev == NULL)
        ht->shead = new_node;  // New head
    else
        prev->snext = new_node;

    if (sorted_current != NULL)
        sorted_current->sprev = new_node;  // Set previous node

    if (sorted_current == NULL)
        ht->stail = new_node;  // New tail if at the end

    return (1);
}

/**
 * shash_table_get - Retrieves a value associated with a key
 * @ht: The hash table
 * @key: The key
 *
 * Return: The value associated with the key, or NULL if not found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
    unsigned long int index;
    shash_node_t *node;

    if (ht == NULL || key == NULL)
        return (NULL);

    index = key_index((const unsigned char *)key, ht->size);
    node = ht->array[index];

    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
            return (node->value);
        node = node->next;
    }

    return (NULL);
}

/**
 * shash_table_print - Prints the hash table
 * @ht: The hash table
 */
void shash_table_print(const shash_table_t *ht)
{
    shash_node_t *node;
    int first = 1;

    if (ht == NULL)
        return;

    printf("{");
    node = ht->shead;
    while (node != NULL)
    {
        if (!first)
            printf(", ");
        printf("'%s': '%s'", node->key, node->value);
        first = 0;
        node = node->snext;
    }
    printf("}\n");
}

/**
 * shash_table_print_rev - Prints the hash table in reverse order
 * @ht: The hash table
 */
void shash_table_print_rev(const shash_table_t *ht)
{
    shash_node_t *node;
    int first = 1;

    if (ht == NULL)
        return;

    printf("{");
    node = ht->stail;
    while (node != NULL)
    {
        if (!first)
            printf(", ");
        printf("'%s': '%s'", node->key, node->value);
        first = 0;
        node = node->sprev;
    }
    printf("}\n");
}

/**
 * shash_table_delete - Deletes a hash table
 * @ht: The hash table to delete
 */
void shash_table_delete(shash_table_t *ht)
{
    shash_node_t *node, *temp;
    unsigned long int i;

    if (ht == NULL)
        return;

    for (i = 0; i < ht->size; i++)
    {
        node = ht->array[i];
        while (node != NULL)
        {
            temp = node;
            node = node->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }

    free(ht->array);
    free(ht);
}

/**
 * key_index - Computes the index for a key
 * @key: The key
 * @size: The size of the array
 *
 * Return: The index at which the key/value pair should be stored
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
    // A simple hash function implementation
    unsigned long int hash = 5381;
    int c;

    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return (hash % size);
}

