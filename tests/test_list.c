#include <la/arc.h>

void free_data(void *data) {
    free(data);
}

int main(void) {
    printf("Linked list unit tests\n");

    List *list = malloc(sizeof(List));
    assert(list != NULL);
    la_list_init(list, free_data);

    int *val1 = malloc(sizeof(int));
    *val1 = 10;
    int status = la_list_ins_next(list, NULL, val1);
    assert(status == 0);

    int *val2 = malloc(sizeof(int));
    *val2 = 20;
    status = la_list_ins_next(list, NULL, val2);
    assert(status == 0);

    void *data_out;

    status = la_list_rem_next(list, NULL, &data_out);
    assert(status == 0);
    assert(*(int *)data_out == 20);
    free(data_out);

    status = la_list_rem_next(list, NULL, &data_out);
    assert(status == 0);
    assert(*(int *)data_out == 10);
    free(data_out);

    status = la_list_rem_next(list, NULL, &data_out);
    assert(status == -1);

    int *val3 = malloc(sizeof(int));
    *val3 = 30;
    la_list_ins_next(list, NULL, val3);

    la_list_destroy(list);
    free(list);

    printf("Linked List tests passed successfully\n");
    return 0;
}
