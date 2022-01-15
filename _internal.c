#include <stdlib.h>

#include "_internal.h"

ll_node_t * _ll_new_node(ll_value_t val, ll_node_t * next)
{
	ll_node_t * res = malloc(sizeof(ll_node_t));
	if (res == NULL)
		return NULL;
	
	res->value = val;
	res->next = next;
	return res;
}
