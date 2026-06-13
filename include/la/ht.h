#ifndef HT_H
#define HT_H

#include <la/list.h>

typedef struct ht_t
{
	int buckets;
	int (*hash)(const void *key);
	int (*match)(const void *k1, const void *k2);
	void (*destroy)(void *data);
	int size;
	List *table;	
} Ht;

int la_ht_init(Ht *htbl, int buckets, int (*hash)(const void *key), int (*match)(const void *k1, const void *k2), void (*destroy)(void *data));
void la_ht_destroy(Ht *htbl);
int la_ht_insert(Ht *htbl, const void *data);
int la_ht_set_remove(Ht *htbl, void **data);
int la_ht_set_lookup(Ht *htbl, void **data);

#define ht_size(ht) ((ht)->size)

#endif
