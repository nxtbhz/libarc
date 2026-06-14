#include <arc/ds/ht.h>

int arc_ht_init(Ht *htbl, int buckets, int (*hash)(const void *key), int (*match)(const void *k1, const void *k2), void (*destroy)(void *data))
{
	if((htbl->table = malloc(sizeof(List) * buckets)) == NULL)
	{
		return -1;	
	}

	htbl->buckets = buckets;
	htbl->hash = hash;
	htbl->destroy = destroy;
	htbl->match = match;
	htbl->size = 0;

	for(int i = 0; i < buckets; i++)
	{
		arc_list_init(&htbl->table[i], destroy);
	}
	return 0;
}

void arc_ht_destroy(Ht *htbl)
{
	for(int i = 0; i < htbl->buckets; i++)
	{
		arc_list_destroy(&htbl->table[i]);
	}
	free(htbl->table);
	memset(htbl, 0, sizeof(Ht));
	return;
}

int arc_ht_insert(Ht *htbl, const void *data)
{
	void *tmp = (void *) data;
	int bucket, retval;

	if(arc_ht_set_lookup(htbl, &tmp) == 0)
	{
		return 1;
	}

	bucket = htbl->hash(data) % htbl->buckets;
	
	if((retval = arc_list_ins_next(&htbl->table[bucket], NULL, data)) == 0)
	{
		htbl->size++;
	}

	return retval;	
}

int arc_ht_set_remove(Ht *htbl, void **data)
{
	int bucket = htbl->hash(*data) % htbl->buckets;

	ListNode *prev = NULL;

	for(ListNode *rem = list_head(&htbl->table[bucket]); rem != NULL; rem = list_next(rem))
	{		
		if(htbl->match(*data, list_data(rem)))
		{
			if(arc_list_rem_next(&htbl->table[bucket], prev, data) == 0){
				htbl->size--;
				return 0;
			}
			else 
			{
				return -1;
			}
		}
		prev = rem;
	}
	return -1;
}

int arc_ht_set_lookup(Ht *htbl, void **data)
{
	int bucket = htbl->hash(*data) % htbl->buckets;

	for(ListNode *rem = list_head(&htbl->table[bucket]); rem != NULL; rem = list_next(rem))
	{
		if(htbl->match(*data, list_data(rem)))
		{
			*data = list_data(rem);
			return 0;
		}
	}	
	return -1;
}


