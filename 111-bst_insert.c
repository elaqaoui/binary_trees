#include "binary_trees.h"

/**
 * bst_insert - Inserts a value in a Binary Search Tree.
 * @tree: A double pointer to the root node of the BST to insert the value.
 * @value: The value to store in the node to be inserted.
 *
 * Return: A pointer to the created node, or NULL on failure.
 */
bst_t *bst_insert(bst_t **tree, int value)
{
	bst_t *currente, *new_n;

	if (tree != NULL)
	{
		currente = *tree;

		if (currente == NULL)
		{
			new_n = binary_tree_node(currente, value);
			if (new_n == NULL)
				return (NULL);
			return (*tree = new_n);
		}

		if (value < currente->n) /* insert in left subtree */
		{
			if (currente->left != NULL)
				return (bst_insert(&currente->left, value));

			new_n = binary_tree_node(currente, value);
			if (new_n == NULL)
				return (NULL);
			return (currente->left = new_n);
		}
		if (value > currente->n) /* insert in right subtree */
		{
			if (currente->right != NULL)
				return (bst_insert(&currente->right, value));

			new_n = binary_tree_node(currente, value);
			if (new_n == NULL)
				return (NULL);
			return (currente->right = new_n);
		}
	}
	return (NULL);
}
