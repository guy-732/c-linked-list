#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H

#include <stdint.h>
#include <stdbool.h>

#ifndef VALUE_TYPE
#define VALUE_TYPE void *
#endif

typedef VALUE_TYPE ll_value_t;
typedef int (*cmp_func_t)(ll_value_t, ll_value_t);
typedef void (*consume_func_t)(ll_value_t);

typedef struct ll_node_t
{
	ll_value_t value;

	ll_node_t * prev;
	ll_node_t * next;
} ll_node_t;

typedef struct linked_list_t
{
	ll_node_t * head;
	ll_node_t * tail;

	cmp_func_t cmp;
} linked_list_t;


#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Initialize a linked list
 * if cmp is NULL some functions will not be usable
 */
void ll_init(linked_list_t * ll, cmp_func_t cmp);

/*
 * Remove all elements of the linked list (from head to tail)
 * calling the `consume_func_t f` on each element before removing them if `f != NULL`
 */
void ll_clear(linked_list_t * ll, consume_func_t f);

/*
 * returns the number of node in the linked list, if ll == NULL, 0 will be returned
 */
uint64_t ll_len(linked_list_t * ll);

/*
 * returns true on sucess, false on failure
 * (ll == NULL || res == NULL) -> errno = EINVAL | index is out of range -> errno = ERANGE
 * (yes ERANGE isn't supposed to be used for that but, meh)
 * 
 * if index >= 0 will start from head, if index < 0 will start from tail (like python list/tuple)
 * index = 0 -> returns head value | index = -1 -> returns tail value
 */
bool ll_get_item(linked_list_t * ll, int32_t index, ll_value_t * res);

#ifdef __cplusplus
}
#endif

#endif
