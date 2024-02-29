#include "binary_trees.h"

size_t height(const binary_tree_t *tree);
int balance(const binary_tree_t *tree);
avl_t *recursive_avl_insert(avl_t **tree, avl_t *parent,
		avl_t **new_n, int value);
avl_t *avl_insert(avl_t **tree, int value);

/**
 * height - Measures the height of a binary tree.
 * @tree: A pointer to the root node of the tree to measure the height.
 *
 * Return: If tree is NULL, your function must return 0, else return height.
 */
size_t height(const binary_tree_t *tree)
{
	if (tree != NULL)
	{
		size_t l = 0, r = 0;

		l = tree->left ? 1 + binary_tree_height(tree->left) : 1;
		r = tree->right ? 1 + binary_tree_height(tree->right) : 1;
		return ((l > r) ? l : r);
	}
	return (0);
}

/**
 * balance - Measures the balance factor of a binary tree.
 * @tree: A pointer to the root node of the tree to measure the balance factor.
 *
 * Return: If tree is NULL, return 0, else return balance factor.
 */
int balance(const binary_tree_t *tree)
{
	return (tree != NULL ? height(tree->left) - height(tree->right) : 0);
}

/**
 * recursive_avl_insert - Inserts a value into an AVL tree recursively.
 * @tree: A double pointer to the root node of the AVL tree to insert into.
 * @parent: The parent node of the current working node.
 * @new_n: A double pointer to store the new_n node.
 * @value: The value to insert into the AVL tree.
 *
 * Return: A pointer to the new_n root after insertion, or NULL on failure.
 */
avl_t *recursive_avl_insert(avl_t **tree, avl_t *parent,
		avl_t **new_n, int value)
{
	int factb;

	if (*tree == NULL)
		return (*new_n = binary_tree_node(parent, value));

	if ((*tree)->n > value)
	{
		(*tree)->left = recursive_avl_insert(&(*tree)->left, *tree, new_n, value);
		if ((*tree)->left == NULL)
			return (NULL);
	}
	else if ((*tree)->n < value)
	{
		(*tree)->right = recursive_avl_insert(&(*tree)->right, *tree, new_n, value);
		if ((*tree)->right == NULL)
			return (NULL);
	}
	else
		return (*tree);

	factb = balance(*tree);
	if (factb > 1 && (*tree)->left->n > value)
		*tree = binary_tree_rotate_right(*tree);
	else if (factb < -1 && (*tree)->right->n < value)
		*tree = binary_tree_rotate_left(*tree);
	else if (factb > 1 && (*tree)->left->n < value)
	{
		(*tree)->left = binary_tree_rotate_left((*tree)->left);
		*tree = binary_tree_rotate_right(*tree);
	}
	else if (factb < -1 && (*tree)->right->n > value)
	{
		(*tree)->right = binary_tree_rotate_right((*tree)->right);
		*tree = binary_tree_rotate_left(*tree);
	}

	return (*tree);
}

/**
 * avl_insert - Inserts a value into an AVL tree.
 * @tree: A double pointer to the root node of the AVL tree to insert into.
 * @value: The value to insert into the AVL tree.
 *
 * Return: A pointer to the inserted node, or NULL on failure.
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *new_n = NULL;

	if (tree == NULL)
		return (NULL);
	if (*tree == NULL)
	{
		*tree = binary_tree_node(NULL, value);
		return (*tree);
	}
	recursive_avl_insert(tree, *tree, &new_n, value);
	return (new_n);
}
