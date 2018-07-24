#include "llist.h"

#define SLICE(N, HEAD) ({ \
        struct list_head *pos = (HEAD); \
        for (int __i = 1 ; \
                (__i < (N)); \
                (pos = (pos->next)), __i++); \
        pos->next = (HEAD); \
        (HEAD)->prev = pos; \
        HEAD; \
})

#define SLICE_BW(N, HEAD) ({ \
        struct list_head *tail = (HEAD)->prev; \
        struct list_head *pos = tail; \
        for (int __i = 1 ; \
                (__i < (N)); \
                (pos = (pos->prev)), __i++); \
        pos->prev = tail; \
        tail->next = pos; \
        pos; \
})

#define TRAVERSE_BW(HEAD, POS) \
        for ( POS = ((HEAD)->prev) ; POS ; \
                (POS = (POS->prev)), POS = (POS != ((HEAD)->prev)? POS : NULL))

void init_list_head(struct list_head *hd) {
        hd->next = hd;
        hd->prev = hd;
}

void insert_node(struct list_head *head, struct list_head *ins, unsigned int position) {
        int count = 0;
        struct list_head *pos;
        TRAVERSE(head, pos) {
                if (count == position) {
                        struct list_head *temp = pos->next;
                        ins->next = pos->next;
                        ins->prev = pos;

                        pos->next = ins;
                        temp->prev = ins;
                        break;
                }
                count++;
        }
}

void remove_node(struct list_head *head, struct list_head *node) {
        struct list_head *pos;
        TRAVERSE(head, pos) {
                if (pos == node) {
                        struct list_head *prev = pos->prev;
                        struct list_head *next = pos->next;
                        prev->next = next;
                        next->prev = prev;
                        break;
                }
        }
}

void clear(struct list_head *head, void(*deinit)(struct list_head *)) {
        struct list_head *prev, *pos = head->next;
        while (pos != head) {
                prev = pos;
                pos = pos->next;
                init_list_head(prev);
                deinit(prev);
        }
        init_list_head(head);
        deinit(head);
}

void tail_add(struct list_head *tail, struct list_head *list) {
        tail->next = list;
        tail->prev = list->prev;
        list->prev->next = tail;
        list->prev = tail;
}

struct list_head* head_add(struct list_head *head, struct list_head *list) {
        struct list_head *temp = list->prev;
        list->prev->next = head;
        list->prev = head;
        head->prev = temp;
        head->next = list;
        return head;
}

struct list_head* reverse(struct list_head *head) {
        /* break the circle */
        head->prev->next = NULL;
        head->prev = NULL;

        struct list_head *prev, *cur, *next;
        prev = NULL;
        cur = head;

        while (cur != NULL) {
                next = cur->next;
                cur->next = prev;
                cur->prev = next;
                prev = cur;
                cur = next;
        }
        /* connect the circle */
        prev->prev = head;
        head->next = prev;
        return prev;
}

static struct list_head* head_remove(struct list_head *list) {
        if (list->next == list)
                return NULL;
        struct list_head* new_head = list->next;
        list->prev->next = new_head;
        new_head->prev = list->prev;
        init_list_head(list);
        return new_head;
}

static struct list_head* merge(struct list_head *left, struct list_head *right,
                        bool(*pred)(struct list_head *, struct list_head *)) {
        if (left == NULL) return right;
        if (right == NULL) return left;

        struct list_head *head, *tail;

        if (pred(left, right)) {
                head = left;
                tail = head_remove(left);
                return head_add(head, merge(tail, right, pred));
        } else {
                head = right;
                tail = head_remove(right);
                return head_add(head, merge(left, tail, pred));
        }
}

struct list_head* merge_sort(struct list_head *head) {

        if (head->next == head) return head;
        int c = COUNT(head);
        struct list_head *last_few = SLICE_BW(c/2, head);
        struct list_head *first_few = SLICE(c%2 ? c/2+1 : c/2, head);
        return merge(merge_sort(first_few), merge_sort(last_few), predicate);
}

bool predicate(struct list_head *left, struct list_head *right) {
        return false;
}
