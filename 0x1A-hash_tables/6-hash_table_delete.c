#include <stdlib.h>
#include <string.h>
#include "hash_tables.h"

/**
 * hash_table_delete - Deletes a hash table
 * @ht: The hash table to delete
 */
void hash_table_delete(hash_table_t *ht)
{
    hash_node_t *node, *temp;
    unsigned long int i;

    if (ht == NULL)
        return;

    // Iterate through the array
    for (i = 0; i < ht->size; i++)
    {
        node = ht->array[i];
        // Free each linked list
        while (node != NULL)
        {
            temp = node;
            node = node->next;
            free(temp->key);    // Free the key
            free(temp->value);  // Free the value
            free(temp);         // Free the node
        }
    }

    free(ht->array);          // Free the array
    free(ht);                 // Finally, free the hash table itself
}

