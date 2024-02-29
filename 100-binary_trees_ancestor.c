#include "binary_trees.h"

/**
 * binary_trees_ancestor - Finds the lowest common ancestor of two nodes.
 * @first: Pointer to the first node.
 * @second: Pointer to the second node.
 *
 * Return: If no common ancestors return NULL, else return common ancestor.
 */
binary_tree_t *binary_trees_ancestor(const binary_tree_t *first,
		const binary_tree_t *second)
{
	binary_tree_t *man, *pip;

	if (!first || !second)
		return (NULL);
	if (first == second)
		return ((binary_tree_t *)first);

	man = first->parent, pip = second->parent;
	if (first == pip || !man || (!man->parent && pip))
		return (binary_trees_ancestor(first, pip));
	else if (man == second || !pip || (!pip->parent && man))
		return (binary_trees_ancestor(man, second));
	return (binary_trees_ancestor(man, pip));
}
