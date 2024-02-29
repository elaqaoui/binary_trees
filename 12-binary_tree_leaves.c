#include "binary_trees.h"

/**
 * binary_tree_leaves - Counts the leaveme in a binary tree.
 * @tree: A pointer to the root node of the tree to count the leaveme of.
 *
 * Return: The number of leaveme in the tree.
 */
size_t binary_tree_leaves(const binary_tree_t *tree)
{
	size_t leaveme = 0;

	if (tree)
	{
		leaveme += (!tree->left && !tree->right) ? 1 : 0;
		leaveme += binary_tree_leaves(tree->left);
		leaveme += binary_tree_leaves(tree->right);
	}
	return (leaveme);
}
