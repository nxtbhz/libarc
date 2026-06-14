#include <arc/ds/bitree.h>

void arc_bitree_init(BiTree *tree, void (*destroy)(void *data))
{
    tree->size = 0;
    tree->root = NULL;
    tree->destroy = destroy;
    return;
}

void arc_bitree_destroy(BiTree *tree)
{
    arc_bitree_rem_left(tree, NULL);

    memset(tree, 0, sizeof(BiTree));

    return;
}

int arc_bitree_ins_left(BiTree *tree, BiTreeNode *element, const void *data)
{
    BiTreeNode *new_node, **position;

    if (element == NULL)
    {
        if (bitree_size(tree) > 0)
            return -1;
        position = &tree->root;
    }
    else
    {
        if (bitree_left(element) != NULL)
            return -1;
        position = &element->left;
    }

    if ((new_node = malloc(sizeof(BiTreeNode))) == NULL)
        return -1;

    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    tree->size++;
    return 0;
}

int arc_bitree_ins_right(BiTree *tree, BiTreeNode *element, const void *data) {
    BiTreeNode *new_node, **position;

    if (element == NULL) {
        if (bitree_size(tree) > 0)
            return -1;
        position = &tree->root;
    } else {
        if (bitree_right(element) != NULL)
            return -1;
        position = &element->right;
    }

    if ((new_node = malloc(sizeof(BiTreeNode))) == NULL)
        return -1;

    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    *position = new_node;

    tree->size++;
    return 0;
}

void arc_bitree_rem_left(BiTree *tree, BiTreeNode *node)
{
    if (bitree_size(tree) == 0)
    {
        return;
    }

    BiTreeNode **pos;

    if (*pos == NULL)
    {
        pos = &tree->root;
    }
    else
    {
        pos = &node->left;
    }

    if (*pos != NULL)
    {
        arc_bitree_rem_left(tree, *pos);
        arc_bitree_rem_right(tree, *pos);

        if (tree->destroy != NULL)
        {
            tree->destroy((*pos)->data);
        }
        free(*pos);
        *pos = NULL;
        tree->size--;
    }
    return 0;
}

void arc_bitree_rem_right(BiTree *tree, BiTreeNode *node)
{
    if (bitree_size(tree) == 0)
    {
        return;
    }

    BiTreeNode **pos;

    if (*pos == NULL)
    {
        pos = &tree->root;
    }
    else
    {
        pos = &node->right;
    }

    if (*pos != NULL)
    {
        arc_bitree_rem_left(tree, *pos);
        arc_bitree_rem_right(tree, *pos);

        if (tree->destroy != NULL)
        {
            tree->destroy((*pos)->data);
        }
        free(*pos);
        *pos = NULL;
        tree->size--;
    }
    return 0;
}

int arc_bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data) {
    arc_bitree_init(merge, left->destroy);

    if (arc_bitree_ins_left(merge, NULL, data) != 0) {
        arc_bitree_destroy(merge);
        return -1;
    }

    bitree_root(merge)->left = bitree_root(left);
    bitree_root(merge)->right = bitree_root(right);

    merge->size = merge->size + bitree_size(left) + bitree_size(right);

    left->root = NULL;
    left->size = 0;
    right->root = NULL;
    right->size = 0;

    return 0;
}
