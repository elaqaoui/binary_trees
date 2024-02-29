#include "binary_trees.h"
#include "limits.h"

size_t height(const binary_tree_t *tree);
int helper_func_avl(const binary_tree_t *tree, int lg, int hi);
int binary_tree_is_avl(const binary_tree_t *tree);

/**
 * height - Measures the height of a binary tree.
 * @tree: A pointer to the root node of the tree to measure the height.
 *
 * Return: If tree is NULL, your function must return 0, else return height.
 */
size_t height(const binary_tree_t *tree)
{
	if (tree)
	{
		size_t l = 0, r = 0;

		l = tree->left ? 1 + height(tree->left) : 1;
		r = tree->right ? 1 + height(tree->right) : 1;
		return ((l > r) ? l : r);
	}
	return (0);
}

/**
 * helper_func_avl - Checks if a binary tree is a valid AVL tree.
 * @tree: A pointer to the root node of the tree to check.
 * @lg: The value of the smallest node visited thus far.
 * @hi: The value of the largest node visited this far.
 *
 * Return: If the tree is a valid AVL tree, 1, otherwise, 0.
 */
int helper_func_avl(const binary_tree_t *tree, int lg, int hi)
{
	size_t lefht, riht, dif;

	if (tree != NULL)
	{
		if (tree->n < lg || tree->n > hi)
			return (0);
		lefht = height(tree->left);
		riht = height(tree->right);
		dif = lefht > riht ? lefht - riht : riht - lefht;
		if (dif > 1)
			return (0);
		return (helper_func_avl(tree->left, lg, tree->n - 1) &&
			helper_func_avl(tree->right, tree->n + 1, hi));
	}
	return (1);
}

/**
 * binary_tree_is_avl - Checks if a binary tree is a valid AVL tree.
 * @tree: A pointer to the root node of the tree to check.
 *
 * Return: 1 if tree is a valid AVL tree, and 0 otherwise
 */
int binary_tree_is_avl(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);
	return (helper_func_avl(tree, INT_MIN, INT_MAX));
}
