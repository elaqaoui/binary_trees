#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_trees.h"

/* Original code from http://stackoverflow.com/a/13755911/5184480 */

/**
 * print_t - Stores recursively each level in an array of strings
 *
 * @tree: Pointer to the node to print
 * @offsetv: Offset to print
 * @depth: Depth of the node
 * @s: Buffer
 *
 * Return: length of printed tree after process
 */
static int print_t(const binary_tree_t *tree, int offsetv, int depth, char **s)
{
	char b[6];
	int width, left, right, are_left, i;

	if (!tree)
		return (0);
	are_left = (tree->parent && tree->parent->left == tree);
	width = sprintf(b, "(%03d)", tree->n);
	left = print_t(tree->left, offsetv, depth + 1, s);
	right = print_t(tree->right, offsetv + left + width, depth + 1, s);
	for (i = 0; i < width; i++)
		s[depth][offsetv + left + i] = b[i];
	if (depth && are_left)
	{
		for (i = 0; i < width + right; i++)
			s[depth - 1][offsetv + left + width / 2 + i] = '-';
		s[depth - 1][offsetv + left + width / 2] = '.';
	}
	else if (depth && !are_left)
	{
		for (i = 0; i < left + width; i++)
			s[depth - 1][offsetv - width / 2 + i] = '-';
		s[depth - 1][offsetv + left + width / 2] = '.';
	}
	return (left + width + right);
}

/**
 * _height - Measures the height of a binary tree
 *
 * @tree: Pointer to the node to measures the height
 *
 * Return: The height of the tree starting at @node
 */
static size_t _height(const binary_tree_t *tree)
{
	size_t lsub_height;
	size_t rsub_height;

	lsub_height = tree->left ? 1 + _height(tree->left) : 0;
	rsub_height = tree->right ? 1 + _height(tree->right) : 0;
	return (lsub_height > rsub_height ? lsub_height : rsub_height);
}

/**
 * binary_tree_print - Prints a binary tree
 *
 * @tree: Pointer to the root node of the tree to print
 */
void binary_tree_print(const binary_tree_t *tree)
{
	char **s;
	size_t height, i, w;

	if (!tree)
		return;
	height = _height(tree);
	s = malloc(sizeof(*s) * (height + 1));
	if (!s)
		return;
	for (i = 0; i < height + 1; i++)
	{
		s[i] = malloc(sizeof(**s) * 255);
		if (!s[i])
			return;
		memset(s[i], 32, 255);
	}
	print_t(tree, 0, 0, s);
	for (i = 0; i < height + 1; i++)
	{
		for (w = 254; w > 1; --w)
		{
			if (s[i][w] != ' ')
				break;
			s[i][w] = '\0';
		}
		printf("%s\n", s[i]);
		free(s[i]);
	}
	free(s);
}
