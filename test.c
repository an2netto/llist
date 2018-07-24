#include "llist.h"

struct my_kernail_list {
        int data;
        char c;
        struct list_head list;
};

bool predicate(struct list_head *hdl, struct list_head *hdr) {
        struct my_kernail_list *l = list_entry(hdl, struct my_kernail_list, list);
        struct my_kernail_list *r = list_entry(hdr, struct my_kernail_list, list);
        return l->data < r->data;
}

void deinit(struct list_head *head) {
        struct my_kernail_list *item = list_entry(head, struct my_kernail_list, list);
        free(item);
}

int main()
{
        struct my_kernail_list *temp;
        struct list_head *new_head;

        temp = malloc(sizeof *temp);
        init_list_head(&temp->list);
        temp->data = 700;
        temp->c = 'a';

        new_head = &temp->list;

        printf("\n**tail_add\n");
        for (int i=1; i<7; i++) {
                temp = malloc(sizeof *temp);
                init_list_head(&temp->list);
                temp->data = rand()%1000;
                temp->c = 'a' + i;
                tail_add(&temp->list, new_head);
        }

        struct list_head *pos;
        TRAVERSE(new_head, pos) {
                struct my_kernail_list *item = list_entry(pos, struct my_kernail_list, list);
                printf("data=%d c=%c\n", item->data, item->c);
        }

        printf("\n**count=%d\n**list_member_offset=%ld\n", COUNT(new_head),
                (unsigned long)(&((struct my_kernail_list *)0)->list));

        printf("\n**merge_sort\n");
        new_head = merge_sort(new_head);

        TRAVERSE(new_head, pos) {
                struct my_kernail_list *item = list_entry(pos, struct my_kernail_list, list);
                printf("data=%d c=%c\n", item->data, item->c);
        }

        printf("\n**reverse\n");
        new_head = reverse(new_head);

        TRAVERSE(new_head, pos) {
                struct my_kernail_list *item = list_entry(pos, struct my_kernail_list, list);
                printf("data=%d c=%c\n", item->data, item->c);
        }

        temp = malloc(sizeof *temp);
        init_list_head(&temp->list);
        temp->data = 9;
        temp->c = 'X';

        printf("\n**insert node after index 1: data=%d c=%c\n", temp->data, temp->c);
        insert_node(new_head, &temp->list, 1);

        TRAVERSE(new_head, pos) {
                struct my_kernail_list *item = list_entry(pos, struct my_kernail_list, list);
                printf("data=%d c=%c\n", item->data, item->c);
        }

        printf("\n**remove node: data=%d c=%c\n", temp->data, temp->c);
        remove_node(new_head, &temp->list);
        free(temp);

        TRAVERSE(new_head, pos) {
                struct my_kernail_list *item = list_entry(pos, struct my_kernail_list, list);
                printf("data=%d c=%c\n", item->data, item->c);
        }

        printf("\n**clear\n\n");
        clear(new_head, deinit);

        return 0;
}
