#include <stdio.h>
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

	ll->size = 0;
}

uint64_t ll_len(const linked_list_t * ll)
{
	#ifdef DEBUG
	uint64_t l = 0;
	ll_node_t * n;

	if (ll == NULL)
	{
		errno = EINVAL;
		return 0;
	}

	n = ll->head;

	while (n != NULL)
	{
		++l;
		n = n->next;
	}

	if (l != ll->size)
		fprintf(stderr, "WARNING FILE %s LINE %d: counted %lu nodes in linked list @%p "
				"while internal count is %ld (value changed to match)\n",
				__FILE__, __LINE__, l, ll, ll->size);
	#endif

	return ll->size;
}

bool ll_get_item(linked_list_t * ll, int32_t index, ll_value_t * res)
{
	if (ll == NULL || res == NULL)
	{
		errno = EINVAL;
		return false;
	}

	int32_t i;
	ll_node_t * n;
	if (index < 0)
	{
		n = ll->tail;
		if (n == NULL)
		{
			errno = ERANGE;
			return false;
		}

		for (i = -1; i > index; --i)
		{
			if (n->prev == NULL)
			{
				errno = ERANGE;
				return false;
			}

			n = n->prev;
		}

		*res = n->value;
		return true;
	}

	n = ll->head;
	if (n == NULL)
	{
		errno = ERANGE;
		return false;
	}

	for (i = 0; i < index; ++i)
	{
		if (n->next == NULL)
		{
			errno = ERANGE;
			return false;
		}

		n = n->next;
	}

	*res = n->value;
	return true;
}

bool ll_set_item(linked_list_t * ll, int32_t index, ll_value_t val)
{
	if (ll == NULL)
	{
		errno = EINVAL;
		return false;
	}

	int32_t i;
	ll_node_t * n;
	if (index < 0)
	{
		n = ll->tail;
		if (n == NULL)
		{
			errno = ERANGE;
			return false;
		}

		for (i = -1; i > index; --i)
		{
			if (n->prev == NULL)
			{
				errno = ERANGE;
				return false;
			}

			n = n->prev;
		}

		n->value = val;
		return true;
	}

	n = ll->head;
	if (n == NULL)
	{
		errno = ERANGE;
		return false;
	}

	for (i = 0; i < index; ++i)
	{
		if (n->next == NULL)
		{
			errno = ERANGE;
			return false;
		}

		n = n->next;
	}

	n->value = val;
	return true;
}

bool ll_remove_item(linked_list_t * ll, int32_t index, ll_value_t * res)
{
	if (ll == NULL)
	{
		errno = EINVAL;
		return false;
	}

	int32_t i;
	ll_node_t * n;
	if (index < 0)
	{
		n = ll->tail;
		if (n == NULL)
		{
			errno = ERANGE;
			return false;
		}

		for (i = -1; i > index; --i)
		{
			if (n->prev == NULL)
			{
				errno = ERANGE;
				return false;
			}

			n = n->prev;
		}
	}
	else
	{
		n = ll->head;
		if (n == NULL)
		{
			errno = ERANGE;
			return false;
		}

		for (i = 0; i < index; ++i)
		{
			if (n->next == NULL)
			{
				errno = ERANGE;
				return false;
			}

			n = n->next;
		}
	}

	if (n->next != NULL)
		n->next->prev = n->prev;
	
	if (n->prev != NULL)
		n->prev->next = n->next;
	
	if (n == ll->head)
		ll->head = n->next;
	
	if (n == ll->tail)
		ll->tail = n->prev;
	
	ll->size--;

	if (res != NULL)
		*res = n->value;
	
	_ll_free_node(n);

	return true;
}

bool ll_insert_head(linked_list_t * ll, ll_value_t val)
{
	if (ll == NULL)
	{
		errno = EINVAL;
		return false;
	}

	ll_node_t * n = _ll_new_node(val, NULL, ll->head);
	if (n == NULL)
		return false;
	
	if (n->next != NULL)
		n->next->prev = n;
	
	ll->head = n;
	ll->size++;
	return true;
}

bool ll_insert_tail(linked_list_t * ll, ll_value_t val)
{
	if (ll == NULL)
	{
		errno = EINVAL;
		return false;
	}

	ll_node_t * n = _ll_new_node(val, ll->tail, NULL);
	if (n == NULL)
		return false;
	
	if (n->prev != NULL)
		n->prev->next = n;
	
	ll->tail = n;
	ll->size++;
	return true;
}
