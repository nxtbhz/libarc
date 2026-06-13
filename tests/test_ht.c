#include <la/arc.h>

int hash_int(const void *key) {
    return *(const int *)key;
}

int match_int(const void *k1, const void *k2) {
    return *(const int *)k1 == *(const int *)k2;
}

void free_data(void *data) {
    free(data);
}

int main(void) {
    printf("Hash table unit tests\n");

    Ht *ht = malloc(sizeof(Ht));
    assert(ht != NULL);

    int status = la_ht_init(ht, 11, hash_int, match_int, free_data);
    assert(status == 0);

    int *val1 = malloc(sizeof(int));
    *val1 = 10;
    status = la_ht_insert(ht, val1);
    assert(status == 0);

    int *val2 = malloc(sizeof(int));
    *val2 = 25;
    status = la_ht_insert(ht, val2);
    assert(status == 0);

    int target1 = 10;
    void *data_look = &target1;
    status = la_ht_set_lookup(ht, &data_look);
    assert(status == 0);
    assert(*(int *)data_look == 10);

    int target2 = 99;
    void *data_look_fail = &target2;
    status = la_ht_set_lookup(ht, &data_look_fail);
    assert(status == -1);

    int target3 = 10;
    void *data_rem = &target3;
    status = la_ht_set_remove(ht, &data_rem);
    assert(status == 0);
    assert(*(int *)data_rem == 10);
    free(data_rem);

    int target4 = 10;
    void *data_rem_fail = &target4;
    status = la_ht_set_remove(ht, &data_rem_fail);
    assert(status == -1);

    int *val3 = malloc(sizeof(int));
    *val3 = 30;
    status = la_ht_insert(ht, val3);
    assert(status == 0);

    la_ht_destroy(ht);
    free(ht);

    printf("Hash Table tests passed successfully\n");
    return 0;
}