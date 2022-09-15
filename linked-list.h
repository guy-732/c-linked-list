#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H

#include <stdint.h>
#include <stdbool.h>

typedef void * ll_value_t;
typedef int (*cmp_func_t)(ll_value_t, ll_value_t);
typedef void (*consume_func_t)(ll_value_t, void * ctx);

typedef struct ll_node_t ll_node_t;

struct ll_node_t
{
	ll_value_t value;

	ll_node_t * prev;
	ll_node_t * next;
};

typedef struct linked_list_t
{
	ll_node_t * head;
	ll_node_t * tail;

	cmp_func_t cmp;
	uint64_t size;
} linked_list_t;


#ifdef __cplusplus
extern "C"
{
#endif

const char * ll_get_version();
const char * ll_get_pkg_name();

/*
 * Initialize a linked list
 * if cmp is NULL some functions will not be usable
 */
void ll_init(linked_list_t * ll, cmp_func_t cmp);

/*
 * Remove all elements of the linked list (from head to tail)
 * calling the `consume_func_t f` on each element before removing them if `f != NULL`
 *
 * function may NOT call longjmp (defined in <setjmp.h>), some blocks won't be freed
 * and the linked list may have some contradicting values as a result
 */
void ll_clear(linked_list_t * ll, consume_func_t f, void * ctx);

/*
 * returns the number of node in the linked list, if ll == NULL, 0 will be returned
 */
#define ll_len(ll) (((const linked_list_t *)(ll))->size)
#define ll_is_empty(ll) (ll_len((ll)) == 0)

/*
 * returns true on sucess, false on failure
 * (ll == NULL || res == NULL) -> errno = EINVAL | index is out of range -> errno = ERANGE
 * (yes ERANGE isn't supposed to be used for that but, meh)
 *
 * if index >= 0 will start from head, if index < 0 will start from tail (like python list/tuple)
 * index = 0 -> returns head value | index = -1 -> returns tail value
 *
 * the value pointed to by `ll_value_t * res` will be set to the value you're getting
 */
bool ll_get_item(const linked_list_t * ll, int64_t index, ll_value_t * res);

/*
 * returns true on sucess, false on failure
 * (ll == NULL) -> errno = EINVAL | index is out of range -> errno = ERANGE
 * (yes ERANGE isn't supposed to be used for that but, meh)
 *
 * This replace an already existing value by another
 */
bool ll_set_item(linked_list_t * ll, int64_t index, ll_value_t val);

/*
 * returns true on sucess, false on failure
 * (ll == NULL) -> errno = EINVAL | index is out of range -> errno = ERANGE
 * (yes ERANGE isn't supposed to be used for that but, meh)
 *
 * if index >= 0 will start from head, if index < 0 will start from tail (like python list/tuple)
 * index = 0 -> remove head | index = -1 -> remove tail
 *
 * if res != NULL, *res will be set to the value you're removing
 */
bool ll_remove_item(linked_list_t * ll, int64_t index, ll_value_t * res);

#define ll_remove_head(ll, res) (ll_remove_item((ll), 0, (res)))
#define ll_remove_tail(ll, res) (ll_remove_item((ll), -1, (res)))

/*
 * remove all corresponding values and return the bumber of elements removed
 * (-1 if ll == NULL || ll->cmp == NULL)
 */
int64_t ll_remove_values(linked_list_t * ll, ll_value_t v);

/*
 * Insert a node at the beggining/end of the linked list,
 * returns true on success, false on failure
 * ll == NULL --> errno = EINVAL
 * if allocation of a new node fails, false will be returned
 */
bool ll_insert_head(linked_list_t * ll, ll_value_t val);
bool ll_insert_tail(linked_list_t * ll, ll_value_t val);


bool ll_search(const linked_list_t * ll, ll_value_t target, int64_t * index, ll_value_t * value);

/*
 * returns true if value is found, false otherwise (or ll == NULL || ll->cmp == NULL)
 * if index != NULL, the first index of the number will be given to the pointed value
 */
#define ll_index_of(ll, target, index) (ll_search((ll), (target), (index), NULL))
#define ll_contains(ll, val) (ll_index_of((ll), (val), NULL))


#ifdef __cplusplus
}
#endif


#ifndef LL_MINIMAL

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Insert a value in sorted order
 * (ll->cmp(val, previous_val) <= 0 && ll->cmp(val, next_val) >= 0)
 *
 * Assumes the linked list is already sorted
 */
bool ll_insert_sorted(linked_list_t * ll, ll_value_t val);

/*
 * find the minimum and maximum value in the linked list
 * and assign the index to the pointer values (if not NULL)
 *
 * returns `false` if the linked list is empty, if ll == NULL or ll->cmp == NULL,
 * errno will be set to EINVAL and `false` returned
 */
bool ll_min_max(
	const linked_list_t * ll,
	ll_value_t * min_ptr, int64_t * min_ind_ptr,
	ll_value_t * max_ptr, int64_t * max_ind_ptr
);
#define ll_min(ll, min_ptr, min_ind_ptr) (ll_min_max((ll), (min_ptr), (min_ind_ptr), NULL, NULL))
#define ll_max(ll, max_ptr, max_ind_ptr) (ll_min_max((ll), NULL, NULL, (max_ptr), (max_ind_ptr)))

/*
 * (ll == NULL || ll->cmp == NULL) => false & errno = EINVAL
 */
bool ll_is_sorted(const linked_list_t * ll);

/*
 * Execute function `f` with all values in `ll` in order (from first to last)
 *
 * `f` may break the iteration by calling longjmp (defined in <setjmp.h>)
 * unlike with `ll_clear`, calling longjmp is safe
 */
void ll_foreach(const linked_list_t * ll, consume_func_t f, void * ctx);

bool ll_add_all(linked_list_t * dest, const linked_list_t * src);

#ifdef __cplusplus
}
#endif

#endif // LL_MINIMAL

#endif // __LINKED_LIST_H
