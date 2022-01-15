#include <stdio.h>
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
		#ifndef DEBUG
		fprintf(stderr, "WARNING FILE %s LINE %d: _ll_swap_nodes received NULL pointer\n",
				__FILE__, __LINE__);
		#endif
		return;
	}

	ll_value_t tmp = n1->value;
	n1->value = n2->value;
	n2->value = tmp;
}
