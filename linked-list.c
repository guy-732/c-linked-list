#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define LL_MINIMAL
#include "linked-list.h"
#include "_ll-internal.h"


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

void ll_clear(linked_list_t * ll, consume_func_t f, void * ctx)
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
			f(n1->value, ctx);

		n2 = n1;
		n1 = n1->next;
		_ll_free_node(n2);
	}

	ll->size = 0;
}

bool ll_get_item(const linked_list_t * ll, int64_t index, ll_value_t * res)
{
	if (ll == NULL || res == NULL)
	{
		errno = EINVAL;
		return false;
	}

	const ll_node_t * n;
	if (!_ll_shorter_index(ll_len(ll), &index))
		return false;

	if (index < 0)
	{
		++index;
		index *= -1;
		n = _ll_get_node_n(ll->tail, index, false);
	}
	else
	{
		n = _ll_get_node_n(ll->head, index, true);
	}

	if (n == NULL)
		return false;

	*res = n->value;
	return true;
}

bool ll_set_item(linked_list_t * ll, int64_t index, ll_value_t val)
{
	if (ll == NULL)
	{
		errno = EINVAL;
		return false;
	}

	ll_node_t * n;
	if (!_ll_shorter_index(ll_len(ll), &index))
		return false;

	if (index < 0)
	{
		++index;
		index *= -1;
		n = _ll_get_node_n(ll->tail, index, false);
	}
	else
	{
		n = _ll_get_node_n(ll->head, index, true);
	}

	if (n == NULL)
		return false;

	n->value = val;
	return true;
}

bool ll_remove_item(linked_list_t * ll, int64_t index, ll_value_t * res)
{
	if (ll == NULL)
	{
		errno = EINVAL;
		return false;
	}

	ll_node_t * n;
	if (!_ll_shorter_index(ll_len(ll), &index))
		return false;

	if (index < 0)
	{
		++index;
		index *= -1;
		n = _ll_get_node_n(ll->tail, index, false);
	}
	else
	{
		n = _ll_get_node_n(ll->head, index, true);
	}

	if (n == NULL)
		return false;

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
	if (ll->tail == NULL)
		ll->tail = n;

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
	if (ll->head == NULL)
		ll->head = n;

	ll->size++;
	return true;
}

bool ll_search(const linked_list_t * ll, ll_value_t target, int64_t * index, ll_value_t * value)
{
	if (ll == NULL || ll->cmp == NULL)
	{
		errno = EINVAL;
		return false;
	}

	int64_t i;
	ll_node_t * n = ll->head;
	for (i = 0; n != NULL; ++i, n = n->next)
	{
		if (ll->cmp(n->value, target) == 0)
		{
			if (index != NULL)
				*index = i;

			if (value != NULL)
				*value = n->value;
			
			return true;
		}
	}

	return false;
}

int64_t ll_remove_values(linked_list_t * ll, ll_value_t v)
{
	int64_t count = 0;
	ll_node_t * n, * tmp;

	if (ll == NULL || ll->cmp == NULL)
	{
		errno = EINVAL;
		return -1;
	}

	for (n = ll->head; n != NULL;)
	{
		if (ll->cmp(n->value, v) == 0) /* n->value == v */
		{
			if (n->next != NULL)
				n->next->prev = n->prev;
			else /* is tail */
				ll->tail = n->prev;

			if (n->prev != NULL)
				n->prev->next = n->next;
			else /* is head */
				ll->head = n->next;

			++count;
			ll->size--;
			tmp = n;
			n = n->next;
			_ll_free_node(tmp);
		}
		else
			n = n->next;
	}

	return count;
}
