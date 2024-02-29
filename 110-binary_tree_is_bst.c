#include "binary_trees.h"
#include "limits.h"

/**
 * my_helper_bt - Checks if a binary tree is a valid binary search tree.
 * @tree: A pointer to the root node of the tree to check.
 * @lg: The value of the smallest node visited thus far.
 * @hi: The value of the largest node visited this far.
 *
 * Return: If the tree is a valid BST, 1, otherwise, 0.
 */
int my_helper_bt(const binary_tree_t *tree, int lg, int hi)
{
	if (tree != NULL)
	{
		if (tree->n < lg || tree->n > hi)
			return (0);
		return (my_helper_bt(tree->left, lg, tree->n - 1) &&
			my_helper_bt(tree->right, tree->n + 1, hi));
	}
	return (1);
}

/**
 * binary_tree_is_bst - Checks if a binary tree is a valid binary search tree.
 * @tree: A pointer to the root node of the tree to check.
 *
 * Return: 1 if tree is a valid BST, and 0 otherwise
 */
int binary_tree_is_bst(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);
	return (my_helper_bt(tree, INT_MIN, INT_MAX));
}
