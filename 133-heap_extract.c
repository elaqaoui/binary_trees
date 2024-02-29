#include "binary_trees.h"

#define INIT_NODE {0, NULL, NULL, NULL}

#define CONVERT "0123456789ABCDEF"

#define SETUP_NODE_BLOC { \
	tempValue = *root; \
	size = binary_tree_size(*root); \
	binary = &buffer[49]; \
	*binary = 0; \
	}

#define FREE_NODE_BLOC { \
		ros = tempValue->n; \
		free(tempValue); \
		*root = NULL; \
	}

#define SWAP_HEAD_BLOC { \
		the_head = *root; \
		the_head = swaping_the_head(the_head, tempValue); \
		ros = the_head->n; \
		free(the_head); \
		*root = tempValue; \
		tempValue = percodown(tempValue); \
		*root = tempValue; \
	}

#define CONVERT_LOOP { \
		*--binary = CONVERT[size % 2]; \
		size /= 2; \
	}

/**
 * swp - swaps two nodes in binary tree
 * @a: first node
 * @b: second node
 * Return: pointer to root
 */
bst_t *swp(bst_t *a, bst_t *b)
{
	bst_t a_copy = INIT_NODE;

	a_copy.n = a->n;
	a_copy.parent = a->parent;
	a_copy.left = a->left;
	a_copy.right = a->right;
	a->parent = b;
	a->left = b->left;
	a->right = b->right;
	if (b->left)
		b->left->parent = a;
	if (b->right)
		b->right->parent = a;

	b->parent = a_copy.parent;
	if (a_copy.parent)
	{
		if (a == a_copy.parent->left)
			a_copy.parent->left = b;
		else
			a_copy.parent->right = b;
	}
	if (b == a_copy.left)
	{
		b->left = a;
		b->right = a_copy.right;
		if (a_copy.right)
			a_copy.right->parent = b;
	}
	else if (b == a_copy.right)
	{
		b->right = a;
		b->left = a_copy.left;
		if (a_copy.left)
			a_copy.left->parent = b;
	}
	while (b->parent)
		b = b->parent;
	return (b);
}

/**
 * binary_tree_size - measures the size of a binary tree
 * @tree: input binary tree
 * Return: number of descendant child nodes
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
	if (!tree)
		return (0);

	return (1 + binary_tree_size(tree->left) + binary_tree_size(tree->right));
}

/**
 * swaping_the_head - helper func to swp the_head and node
 * @the_head: pointer to the_head
 * @node: pointer to node
 * Return: pointer to severed the_head of tree
 */
heap_t *swaping_the_head(heap_t *the_head, heap_t *node)
{
	if (node->parent->left == node)
	{
		node->parent->left = NULL;
	} else
		node->parent->right = NULL;
	node->parent = NULL;
	node->left = the_head->left;
	node->right = the_head->right;
	if (the_head->left)
		the_head->left->parent = node;
	if (the_head->right)
		the_head->right->parent = node;
	return (the_head);
}

/**
 * percodown - percolate the_head into correct position
 * @node: pointer to the_head
 * Return: pointer to the_head of tree
 */
heap_t *percodown(heap_t *node)
{
	int max;
	heap_t *next = node;

	if (!node)
		return (NULL);
	max = node->n;
	if (node->left)
		max = MAX(node->left->n, max);
	if (node->right)
		max = MAX(node->right->n, max);
	if (node->left && max == node->left->n)
		next = node->left;
	else if (node->right && max == node->right->n)
		next = node->right;
	if (next != node)
	{
		swp(node, next);
		percodown(node);
	}
	return (next);
}

/**
 * heap_extract - extracts the root node of a Max Binary Heap
 * @root: double pointer to root of tree
 * Return: value stored in the root node
 */
int heap_extract(heap_t **root)
{
	size_t size, i;
	char *binary, z, buffer[50];
	int ros;
	heap_t *tempValue, *the_head;

	if (!root || !*root)
		return (0);
	SETUP_NODE_BLOC;
	if (size == 1)
	{
		FREE_NODE_BLOC;
		return (ros);
	}
	do {
		CONVERT_LOOP;
	} while (size);

	for (i = 1; i < strlen(binary); i++)
	{
		z = binary[i];
		if (i == strlen(binary) - 1)
		{
			if (z == '1')
			{
				tempValue = tempValue->right;
				break;
			}
			else if (z == '0')
			{
				tempValue = tempValue->left;
				break;
			}
		}
		if (z == '1')
			tempValue = tempValue->right;
		else if (z == '0')
			tempValue = tempValue->left;
	}
	SWAP_HEAD_BLOC;
	return (ros);
}
