#include <errno.h>

#include "ll-extra.h"
#include "_internal.h"

bool ll_insert_sorted(linked_list_t * ll, ll_value_t val)
{
	ll_node_t * n;

	if (ll == NULL || ll->cmp == NULL)
	{
		errno = EINVAL;
		return false;
	}

	if (!ll_insert_head(ll, val))
		return false;

	for (n = ll->head; n->next != NULL; n = n->next)
	{
		if (ll->cmp(n->value, n->next->value) < 0) /* value < next_value */
			return true;

		_ll_swap_nodes(n, n->next);
	}

	return true;
}

bool ll_min_max(linked_list_t * ll, int64_t * min_ptr, int64_t * max_ptr)
{
	int64_t i;
	int64_t min_pos = 0, max_pos = 0;
	ll_value_t min, max;
	ll_node_t * n;

	if (ll == NULL || ll->cmp == NULL)
	{
		errno = EINVAL;
		return false;
	}

	if ((n = ll->head) == NULL)
		return false;

	if (min_ptr == NULL && max_ptr == NULL)
		return true;
	/*
	 * Not a failure, but we don't need to go through the linked list if nothing comes
	 * out of calling this function
	 */

	min = max = n->value;
	n = n->next;

	for (i = 0; n != NULL; n = n->next)
	{
		if (ll->cmp(min, n->value) > 0) /* min > value */
		{
			min_pos = i;
			min = n->value;
		}
		else if (ll->cmp(max, n->value) < 0) /* max < value */
		{
			max_pos = i;
			max = n->value;
		}
	}

	if (min_ptr != NULL)
		*min_ptr = min_pos;

	if (max_ptr != NULL)
		*max_ptr = max_pos;

	return true;
}
