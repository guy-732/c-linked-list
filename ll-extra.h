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
bool ll_min_max(linked_list_t * ll, int64_t * min_ptr, int64_t * max_ptr);
#define ll_min(ll, min_ptr) (ll_min_max((ll), (min_ptr), NULL))
#define ll_max(ll, max_ptr) (ll_min_max((ll), NULL, (max_ptr)))

#ifdef __cplusplus
}
#endif

#endif
