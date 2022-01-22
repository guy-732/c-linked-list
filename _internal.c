#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "_internal.h"

ll_node_t * _ll_new_node(ll_value_t val, ll_node_t * prev, ll_node_t * next)
{
	ll_node_t * res = malloc(sizeof(ll_node_t));
	if (res == NULL)
		return NULL;

	res->value = val;
	res->prev = prev;
	res->next = next;
	return res;
}

void _ll_swap_nodes(ll_node_t * n1, ll_node_t * n2)
{
	if (n1 == NULL || n2 == NULL)
	{
		#ifdef DEBUG
		fprintf(stderr, "WARNING FILE %s LINE %d: _ll_swap_nodes received NULL pointer\n",
				__FILE__, __LINE__);
		#endif
		return;
	}

	ll_value_t tmp = n1->value;
	n1->value = n2->value;
	n2->value = tmp;
}

ll_node_t * _ll_get_node_n(ll_node_t * node, int64_t n, bool forward)
{
	int64_t i;
	if (node == NULL)
	{
		errno = ERANGE;
		return NULL;
	}

	if (forward)
		for (i = 0; i < n; ++i)
		{
			if (node->next == NULL)
			{
				errno = ERANGE;
				return NULL;
			}

			node = node->next;
		}
	else
		for (i = 0; i < n; ++i)
		{
			if (node->prev == NULL)
			{
				errno = ERANGE;
				return NULL;
			}

			node = node->prev;
		}

	return node;
}
