#ifndef ARC_DS_BITREE_H
#define ARC_DS_BITREE_H

#include <stdlib.h>
#include <string.h>
typedef struct bi_tree_node_t
{
	void *data;
	struct bi_tree_node_t *right;
	struct bi_tree_node_t *left;
} BiTreeNode;

typedef struct bi_tree_t
{
	int size;
	int (*compare)(const void *k1, const void *k2);
	void (*destroy)(void *data);
	BiTreeNode *root;
} BiTree;

void arc_bitree_init(BiTree *tree, void (*destroy)(void *data));
void arc_bitree_destroy(BiTree *tree);
int arc_bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data);
int arc_bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data);
void arc_bitree_rem_left(BiTree *tree, BiTreeNode *node);
void arc_bitree_rem_right(BiTree *tree, BiTreeNode *node);
int arc_bitree_merge(BiTree *tree, BiTree *left, BiTree *right, const void *data);

#define bitree_size(tree) ((tree)->size)
#define bitree_root(tree) ((tree)->root)
#define bitree_is_eob(node) (((node) == NULL) ? 1 : 0)
#define bitree_is_leaf(node) (((node)->left == NULL && (node)->right == NULL) ? 1 : 0)
#define bitree_data(node) ((node)->data)
#define bitree_left(node) ((node)->left)
#define bitree_right(node) ((node)->right)

#endif /* ARC_DS_BITREE_H */
