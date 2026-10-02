#ifndef ARC_DS_TST_H
#define ARC_DS_TST_H

struct list_node_t
{
    struct list_node_t *next;
};

struct list_t
{
    int len;
    struct list_node_t *head;
    struct list_node_t *tail;
};

#endif /* ARC_DS_TST_H */
