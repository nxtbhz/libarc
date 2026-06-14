#ifndef ARC_DS_HT_H
#define ARC_DS_HT_H

#include <arc/ds/list.h>
#include <stdlib.h>

typedef struct ht_t
{
	int buckets;
	int (*hash)(const void *key);
	int (*match)(const void *k1, const void *k2);
	void (*destroy)(void *data);
	int size;
	List *table;
} Ht;

int arc_ht_init(Ht *htbl, int buckets, int (*hash)(const void *key), int (*match)(const void *k1, const void *k2), void (*destroy)(void *data));
void arc_ht_destroy(Ht *htbl);
int arc_ht_insert(Ht *htbl, const void *data);
int arc_ht_set_remove(Ht *htbl, void **data);
int arc_ht_set_lookup(Ht *htbl, void **data);

#define ht_size(ht) ((ht)->size)

#endif /* ARC_DS_HT_H */