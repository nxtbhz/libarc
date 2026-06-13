#include <la/arc.h>

int la_ht_init(Ht *htbl, int buckets, int (*hash)(const void *key), int (*match)(const void *k1, const void *k2), void (*destroy)(void *data))
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
		la_list_init(&htbl->table[i], destroy);
	}
	return 0;
}

void la_ht_destroy(Ht *htbl)
{
	for(int i = 0; i < htbl->buckets; i++)
	{
		htbl->table[i]->destroy;
	}
	free(htbl->table);
	memset(htbl, 0, sizeof(Ht));
	return;
}

int la_ht_insert(Ht *htbl, const void *data)
{
	void *tmp = (void *) data;
	int bucket, retval;

	if(la_set_lookup(htbl, &tmp) == 0)
	{
		return 1;
	}

	bucket = htbl->hash(data);
	
	if((retval = la_list_insert_next(htbl->table[bucket], NULL, data)) == 0)
	{
		htbl->size++;
	}

	return retval;	
}

int la_ht_set_remove()
{}

int la_ht_set_lookup()
{}


