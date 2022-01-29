#ifndef __LL_EXTRA_H
#define __LL_EXTRA_H

#include "linked-list.h"

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

void ll_foreach(const linked_list_t * ll, consume_func_t f, void * ctx);

bool ll_add_all(linked_list_t * dest, const linked_list_t * src);

#ifdef __cplusplus
}
#endif

#endif
