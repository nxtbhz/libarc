#ifndef ARC_DS_LIST_H
#define ARC_DS_LIST_H

#include <stdlib.h>
#include <string.h>

typedef struct list_node_t
{
	void *data;
	struct list_node_t *next;
} ListNode;

typedef struct list_t
{
	int size;
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);
	ListNode *head;
	ListNode *tail;
} List;

void arc_list_init(List *list, void (destroy)(void *data));
void arc_list_destroy(List *list);
int arc_list_ins_next(List *list, ListNode *node, const void *data);
int arc_list_rem_next(List *list, ListNode *node, void **data);

#define list_size(list) (list)->size
#define list_head(list) (list)->head
#define list_tail(list) (list)->tail
#define list_is_head(list, element) ((list)->head == (element)) ? 1 : 0
#define list_is_tail(element) ((element)->next == NULL) ? 1 : 0
#define list_data(element) (element)->data 
#define list_next(element) (element)->next

#endif /* ARC_DS_LIST_H */
