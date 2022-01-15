#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "linked-list.h"
#include "_internal.h"


void ll_init(linked_list_t * ll, cmp_func_t cmp)
{
	if (ll == NULL)
	{
		errno = EINVAL;
		return;
	}

	memset(ll, '\0', sizeof(linked_list_t));
	ll->cmp = cmp;
}

void ll_clear(linked_list_t * ll, consume_func_t f)
{
	if (ll == NULL)
	{
		errno = EINVAL;
		return;
	}

	ll_node_t * n1 = ll->head;
	ll_node_t * n2;
	ll->head = ll->tail = NULL;

	while (n1 != NULL)
	{
		if (f != NULL)
			f(n1->value);

		n2 = n1;
		n1 = n1->next;
		_ll_free_node(n2);
	}
}
