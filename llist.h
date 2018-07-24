/**
 * llist: Theory of Operation
 *
 * A set of operations on type oblivious, easy-to-use, circularly-linked list.
 *
 * Same functions are used to initialize, access, and traverse
 * any list of items strung together using this list implementation.
 *
 * Usage:
 *
 * struct my_kernail_list {
 *         int data;
 *         char c;
 *         struct list_head list;
 * };
 *
 * The list is inside the user-defined data item.
 * A member of type struct list_head can be anywhere in the user-defined structure.
 * The struct list_head variable can have any name.
 *
 * The only drawback to this library is its demo-orientation. It is not meant
 * to be embedded into any serious projects.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * list_entry() - A macro function to get a list entry.
 * @ptr:        A pointer to the head of the list.
 * @type:       Type of user-defined data structure
 * @member:     The name of the struct list_head member
 *              in the user-defined data structure
 *
 * Works as a for loop.
 *
 * Return:      A pointer to the user-defined structure which @ptr is a member of
 *
 * Most of the time macro functions is not good.
 */
#define list_entry(ptr, type, member) \
        ( (type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)) )

/**
 * TRAVERSE() - A macro function to iterate over the elements of the list
 * @HEAD:       A pointer to the head of the list.
 * @POS:       An iterative pointer to every element of the list.
 *
 * Works as a for loop.
 *
 * Most of the time macro functions is not good.
 */
#define TRAVERSE(HEAD, POS) \
        for ( POS = (HEAD) ; POS ; \
            (POS = (POS->next)), POS = (POS != (HEAD)? POS : NULL))

/**
 * COUNT() - A macro function to count elements of the list
 * @HEAD:       A pointer to the head of the list.
 *
 * Most of the time macro functions is not good.
 *
 * Return:      number of elements
 */
#define COUNT(HEAD) ({ \
        int __i = 0; \
        for (struct list_head *pos = (HEAD) ; pos ; \
            (pos = (pos->next)), pos = (pos != (HEAD)? pos : NULL), __i++); \
        __i; \
})

/**
 * struct list_head - An instance should be a member of every
 * element of the user-defined data structure.
 *
 * @next: A pointer to the next element of the list.
 * @prev: A pointer to the previous element of the list.
 *
 * Agnostic to other members of the user-defined data structure.
 */
struct list_head {
        struct list_head *next;
        struct list_head *prev;
};

/**
 * init_list_head() - Initialize structure of type struct list_head.
 * @arg1:       A pointer to structure of type struct list_head.
 *
 * Any structure type struct list_head should be initialized with this
 * function to work with this library
 */
void init_list_head(struct list_head *);

/**
 * insert_node() - Initialize structure of type struct list_head.
 * @arg1:       A pointer to the head of the list.
 * @arg2:       A pointer to the head of the element to insert.
 * @arg3:       An index after which the new element will be inserted.
 *
 * If the index is greater than the number of elements in the list,
 * the list will remain unchanged.
 */
void insert_node(struct list_head *, struct list_head *, unsigned int);

/**
 * remove_node() - Remove a specific element from the list.
 * @arg1:       A pointer to the head of the list.
 * @arg2:       A pointer to the head of the element to remove.
 *
 * Memory management is a caller's responsibility. As well as modification
 * of the head of the list.
 *
 * The library does not perform any memory allocation or deallocation.
 */
void remove_node(struct list_head *, struct list_head *);

/**
 * clear() - Make the list empty.
 * @arg1:       A pointer to the head of the list.
 * @arg2:       A callback function for memory management with a pointer to
 *              the element that should be freed.
 *
 * The library does not perform any memory allocation or deallocation.
 */
void clear(struct list_head *, void(*deinit)(struct list_head *));

/**
 * tail_add() - Add an element from the tail of the list.
 * @arg1:       A pointer to the element to be added.
 * @arg2:       A pointer to the head of the list.
 *
 */
void tail_add(struct list_head *, struct list_head *);

/**
 * head_add() - Add an element from the head of the list.
 * @arg1:       A pointer to the element to be added.
 * @arg2:       A pointer to the head of the list.
 *
 * Return:      A pointer to the new head of the list.
 */
struct list_head* head_add(struct list_head *, struct list_head *);

/**
 * reverse() - Reverse the list
 * @arg1:       A pointer to the head of the list.
 *
 * Return:      A pointer to the new head of the list.
 */
struct list_head* reverse(struct list_head *);

/**
 * merge_sort() - Perform a merge sort upon the list.
 * @arg1:       A pointer to the head of the list.
 *
 * Return:      A pointer to the head of the sorted list.
 */
struct list_head* merge_sort(struct list_head *);

/**
 * predicate() - A function that is used by the sorting functions
 * @arg1:       A pointer to the head of the list to be compared with @arg2.
 * @arg2:       A pointer to the head of the list to be compared with @arg1.
 *
 * The function should be implemented by the user of the merge_sort.
 *
 * Return:      true if @arg1 < @arg2, false otherwise.
 */
bool __attribute__((weak)) predicate(struct list_head *, struct list_head *);
