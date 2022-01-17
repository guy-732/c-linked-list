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
			break;

		_ll_swap_nodes(n, n->next);
	}

	return true;
}
