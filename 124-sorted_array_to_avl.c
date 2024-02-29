#include "binary_trees.h"

/**
 * _sorted_avl_array - helper func for sorted_array_to_avl
 * @array: input array
 * @start: starting index
 * @end: ending index
 * @parent: pointer to parent node
 * Return: newly created node
 */
avl_t *_sorted_avl_array(int *array, int start, int end, avl_t *parent)
{
	avl_t *new_n;
	int middle_value;

	if (start > end)
		return (NULL);
	middle_value = (start + end) / 2;
	new_n = calloc(1, sizeof(avl_t));
	if (!new_n)
		return (NULL);
	new_n->n = array[middle_value];
	new_n->parent = parent;
	new_n->left = _sorted_avl_array(array, start, middle_value - 1, new_n);
	new_n->right = _sorted_avl_array(array, middle_value + 1, end, new_n);
	return (new_n);
}


/**
 * sorted_array_to_avl - builds an AVL tree from an array
 * @array: input array
 * @size: size of array
 * Return: pointer to the root node of the created AVL tree, or NULL on failure
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{

	if (!array)
		return (NULL);
	return (_sorted_avl_array(array, 0, size - 1, NULL));
}
