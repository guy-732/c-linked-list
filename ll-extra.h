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

#ifdef __cplusplus
}
#endif

#endif
