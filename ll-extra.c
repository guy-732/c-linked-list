#include <errno.h>
#include <setjmp.h>

#include <linked-list.h>
#include "_ll-internal.h"

#include <config.h>

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
		if (ll->cmp(n->value, n->next->value) > 0) /* value > next_value */
			_ll_swap_nodes(n, n->next);
		else
			return true;

	}

	return true;
}

bool ll_min_max(
	const linked_list_t * ll,
	ll_value_t * min_ptr, int64_t * min_ind_ptr,
	ll_value_t * max_ptr, int64_t * max_ind_ptr
)
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

	if (min_ptr == NULL && max_ptr == NULL && min_ind_ptr == NULL && max_ind_ptr == NULL)
		return true;
	/*
	 * Not a failure, but we don't need to go through the linked list if nothing comes
	 * out of calling this function
	 */

	min = max = n->value;
	n = n->next;

	for (i = 1; n != NULL; ++i, n = n->next)
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

	if (min_ind_ptr != NULL)
		*min_ind_ptr = min_pos;

	if (min_ptr != NULL)
		*min_ptr = min;

	if (max_ind_ptr != NULL)
		*max_ind_ptr = max_pos;

	if (max_ptr != NULL)
		*max_ptr = max;

	return true;
}

bool ll_is_sorted(const linked_list_t * ll)
{
	ll_node_t * n;

	if (ll == NULL || ll->cmp == NULL)
	{
		errno = EINVAL;
		return false;
	}

	if ((n = ll->head) == NULL)
		return true;

	for (; n->next != NULL; n = n->next)
	{
		if (ll->cmp(n->value, n->next->value) > 0) /* val > next-val */
			return false;
	}

	return true;
}

void ll_foreach(const linked_list_t * ll, consume_func_t f, void * ctx)
{
	ll_node_t * n;
	if (ll == NULL || f == NULL)
	{
		errno = EINVAL;
		return;
	}

	for (n = ll->head; n != NULL; n = n->next)
		f(n->value, ctx);
}

typedef struct ll_add_all_ctx_t
{
	linked_list_t * ll;
	jmp_buf j;
} ll_add_all_ctx_t;

static void ll_add_all_consume_func(ll_value_t v, void * ctx);
bool ll_add_all(linked_list_t * dest, const linked_list_t * src)
{
	linked_list_t tmp;
	ll_add_all_ctx_t ctx = {.ll = &tmp};
	ll_node_t * old_tail;

	if (dest == NULL || src == NULL)
	{
		errno = EINVAL;
		return false;
	}

	ll_init(&tmp, NULL);
	if (setjmp(ctx.j) != 0)
	{
		ll_clear(&tmp, NULL, NULL);
		return false;
	}

	ll_foreach(src, ll_add_all_consume_func, &ctx);
	if (tmp.head != NULL)
	{
		old_tail = dest->tail;
		if (old_tail == NULL)
		{
			dest->head = tmp.head;
			dest->tail = tmp.tail;
			dest->size = tmp.size;
		}
		else
		{
			dest->tail = tmp.tail;
			old_tail->next = tmp.head;
			tmp.head->prev = old_tail;
			dest->size += tmp.size;
		}
	}

	return true;
}

static void ll_add_all_consume_func(ll_value_t v, void * ctx)
{
	ll_add_all_ctx_t * c = (ll_add_all_ctx_t *) ctx;
	if (!ll_insert_tail(c->ll, v))
		longjmp(c->j, 1);
}
