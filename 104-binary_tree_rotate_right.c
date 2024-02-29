#include "binary_trees.h"

/**
 * binary_tree_rotate_right - Right-rotates a binary tree.
 * @tree: A pointer to the root node of the tree to rotate.
 *
 * Return: A pointer to the new_n root node after rotation.
 */
binary_tree_t *binary_tree_rotate_right(binary_tree_t *tree)
{
	binary_tree_t *pvt, *tempValue;

	if (tree == NULL || tree->left == NULL)
		return (NULL);

	pvt = tree->left;
	tempValue = pvt->right;
	pvt->right = tree;
	tree->left = tempValue;
	if (tempValue != NULL)
		tempValue->parent = tree;
	tempValue = tree->parent;
	tree->parent = pvt;
	pvt->parent = tempValue;
	if (tempValue != NULL)
	{
		if (tempValue->left == tree)
			tempValue->left = pvt;
		else
			tempValue->right = pvt;
	}

	return (pvt);
}
