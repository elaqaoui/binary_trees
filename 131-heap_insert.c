#include "binary_trees.h"
#include<stdlib.h>
#include<string.h>
#define INIT_NODE {0, NULL, NULL, NULL}

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
 * convert - converts number and base into string
 * @num: input number
 * @base: input base
 * @lowercase: flag if hexa values need to be lowercase
 * Return: result string
 */
char *convert(unsigned long int num, int base, int lowercase)
{
	static char *rep;
	static char buffer[50];
	char *ptr;

	rep = (lowercase)
		? "0123456789abcdef"
		: "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = 0;
	do {
		*--ptr = rep[num % base];
		num /= base;
	} while (num);

	return (ptr);
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
 * insert - helper func to insert node to correct location
 * @root: double pointer to root of max heap
 * @node: node to insert
 */
void insert(heap_t **root, heap_t *node)
{
	heap_t *tempValue;
	int size;
	unsigned int i;
	char *binary;
	char z;

	tempValue = *root;
	size = binary_tree_size(tempValue) + 1;
	binary = convert(size, 2, 1);
	for (i = 1; i < strlen(binary); i++)
	{
		z = binary[i];
		if (i == strlen(binary) - 1)
		{
			if (z == '1')
			{
				node->parent = tempValue;
				tempValue->right = node;
				break;
			}
			else if (z == '0')
			{
				node->parent = tempValue;
				tempValue->left = node;
				break;
			}
		}
		if (z == '1')
			tempValue = tempValue->right;
		else if (z == '0')
			tempValue = tempValue->left;
	}
}


/**
 * heap_insert - inserts a value in Max Binary Heap
 * @root: double pointer to root of tree
 * @value: input value
 * Return: pointer to the created node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *hott = NULL, *rop;

	if (!root)
		return (NULL);
	hott = calloc(1, sizeof(heap_t));
	hott->n = value;
	if (!*root)
	{
		*root = hott;
		return (hott);
	}
	insert(root, hott);
	while (hott->parent && hott->n > hott->parent->n)
	{
		rop = swp(hott->parent, hott);
		if (rop)
			*root = rop;
	}
	return (hott);
}
