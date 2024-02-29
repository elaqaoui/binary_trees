#include "binary_trees.h"

/**
 * array_to_bst - Builds a binary search tree from an array.
 * @array: A pointer to the first element of the array to be converted.
 * @size: The number of elements in @array.
 *
 * Return: A pointer to the root node of the created BST, or NULL upon failure.
 */
bst_t *array_to_bst(int *array, size_t size)
{
	bst_t *tree = NULL;
	size_t i, w;

	if (array == NULL)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		for (w = 0; w < i; w++)
		{
			if (array[w] == array[i])
				break;
		}
		if (w == i)
		{
			if (bst_insert(&tree, array[i]) == NULL)
				return (NULL);
		}
	}

	return (tree);
}
