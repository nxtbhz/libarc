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
int la_ht_insert();
int la_set_remove();
int la_set_lookup();

#define ht_size(ht) ((ht)->size)

#endif
