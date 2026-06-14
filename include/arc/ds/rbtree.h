#ifndef ARC_DS_RBTREE_H
#define ARC_DS_RBTREE_H

#include <arc/ds/bitree.h>

typedef struct rb_node_t
{
    void *data;
    int hidden;
    int factor;
} RbNode;

typedef struct Tree RbTree;

#endif /* ARC_DS_RBTREE_H */