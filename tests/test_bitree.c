#include <assert.h>
#include <stddef.h>
#include <arc/ds/bitree.h>

void dummy_destroy(void *data)
{
    (void)data;
}

void test_arc_bitree_init_and_macros(void)
{
    BiTree tree;
    arc_bitree_init(&tree, dummy_destroy);

    assert(bitree_size(&tree) == 0);
    assert(bitree_root(&tree) == NULL);
    assert(bitree_is_eob(bitree_root(&tree)) == 1);

    arc_bitree_destroy(&tree);
}

void test_arc_bitree_insertion_and_properties(void)
{
    BiTree tree;
    arc_bitree_init(&tree, dummy_destroy);

    int raiz_val = 10;
    int esq_val = 20;
    int dir_val = 30;

    int rc = arc_bitree_ins_left(&tree, NULL, &raiz_val);
    assert(rc == 0);
    assert(bitree_size(&tree) == 1);
    assert(bitree_root(&tree) != NULL);
    assert(*(int *)bitree_data(bitree_root(&tree)) == 10);
    assert(bitree_is_leaf(bitree_root(&tree)) == 1);

    rc = arc_bitree_ins_left(&tree, NULL, &esq_val);
    assert(rc == -1);

    rc = arc_bitree_ins_left(&tree, bitree_root(&tree), &esq_val);
    assert(rc == 0);
    assert(bitree_size(&tree) == 2);
    assert(bitree_is_leaf(bitree_root(&tree)) == 0);
    assert(bitree_is_leaf(bitree_left(bitree_root(&tree))) == 1);

    rc = arc_bitree_ins_left(&tree, bitree_root(&tree), &esq_val);
    assert(rc == -1);

    rc = arc_bitree_ins_right(&tree, bitree_root(&tree), &dir_val);
    assert(rc == 0);
    assert(bitree_size(&tree) == 3);
    assert(bitree_is_leaf(bitree_right(bitree_root(&tree))) == 1);

    arc_bitree_destroy(&tree);
}

void test_arc_bitree_removal(void)
{
    BiTree tree;
    arc_bitree_init(&tree, dummy_destroy);

    int v1 = 1, v2 = 2, v3 = 3;
    arc_bitree_ins_left(&tree, NULL, &v1);
    arc_bitree_ins_left(&tree, bitree_root(&tree), &v2);
    arc_bitree_ins_right(&tree, bitree_root(&tree), &v3);

    assert(bitree_size(&tree) == 3);

    arc_bitree_rem_right(&tree, bitree_root(&tree));
    assert(bitree_size(&tree) == 2);
    assert(bitree_right(bitree_root(&tree)) == NULL);

    arc_bitree_destroy(&tree);
    assert(bitree_size(&tree) == 0);
    assert(bitree_root(&tree) == NULL);
}

void test_arc_bitree_merge(void)
{
    BiTree left_tree, right_tree, merged_tree;

    arc_bitree_init(&left_tree, dummy_destroy);
    arc_bitree_init(&right_tree, dummy_destroy);

    int l_val = 50;
    int r_val = 100;
    int root_val = 75;

    arc_bitree_ins_left(&left_tree, NULL, &l_val);
    arc_bitree_ins_left(&right_tree, NULL, &r_val);

    int rc = arc_bitree_merge(&merged_tree, &left_tree, &right_tree, &root_val);
    assert(rc == 0);

    assert(bitree_size(&merged_tree) == 3);
    assert(*(int *)bitree_data(bitree_root(&merged_tree)) == 75);
    assert(*(int *)bitree_data(bitree_left(bitree_root(&merged_tree))) == 50);
    assert(*(int *)bitree_data(bitree_right(bitree_root(&merged_tree))) == 100);

    assert(bitree_size(&left_tree) == 0);
    assert(bitree_root(&left_tree) == NULL);
    assert(bitree_size(&right_tree) == 0);
    assert(bitree_root(&right_tree) == NULL);

    arc_bitree_destroy(&merged_tree);
}

int main(void)
{
    test_arc_bitree_init_and_macros();
    test_arc_bitree_insertion_and_properties();
    test_arc_bitree_removal();
    test_arc_bitree_merge();

    return 0;
}