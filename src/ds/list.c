#include <arc/ds/list.h>

void arc_list_init(List *list, void (destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->match = NULL;
	list->head = NULL;
	list->tail = NULL;

	return;
}

void arc_list_destroy(List *list)
{
	void *data;
	while(arc_list_rem_next(list, NULL, &data) == 0 && list->destroy != NULL)
	{
		list->destroy(data);	
	}
	memset(list, 0, sizeof(List));
	return;
}

int arc_list_ins_next(List *list, ListNode *node, const void *data)
{
	ListNode *new_element;

	if((new_element = malloc(sizeof(ListNode))) == NULL)
	{
		return -1;
	}

	new_element->data = (void *) data;
	if(node == NULL)
	{
		if(list_size(list) == 0)
		{
			list->tail = new_element;
		}
		new_element->next = list->head;
		list->head = new_element;
	}
	else
	{
		if(list_is_tail(node))
		{
			list->tail = new_element;
		}

		new_element->next = node->next;
		node->next = new_element;
	}

	list->size++;
	return 0;
}

int arc_list_rem_next(List *list, ListNode *node, void **data)
{
	ListNode *rem;
	if(list_size(list) == 0)
	{
		return -1;
	}

	if(node == NULL)
	{
		*data = list->head->data;
		rem = list->head;
		list->head = list->head->next;

		if(list_size(list) == 0)
		{
			list->tail = NULL;
		}

	}	
	else
	{	
		if(node->next == NULL)
		{
			return -1;
		}
		*data = node->next->data;
		rem = node->next;
		node->next = node->next->next;
		
		if(node->next == NULL)
		{
			list->tail = node;
		}
	}
	free(rem);
	list->size--;
	return 0;
}
