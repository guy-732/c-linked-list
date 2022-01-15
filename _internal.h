#ifndef ___INTERNAL_H
#define ___INTERNAL_H

#include <stdlib.h>

#include "linked-list.h"

ll_node_t * _ll_new_node(ll_value_t val, ll_node_t * prev, ll_node_t * next);
#define _ll_free_node(node) (free((node)))

void _ll_swap_nodes(ll_node_t * n1, ll_node_t * n2);

#endif
