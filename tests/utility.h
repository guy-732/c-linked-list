#ifndef __TESTS_UTILITY_H
#define __TESTS_UTILITY_H

#include <stdio.h>

#include "../linked-list.h"

static void clear_func(ll_value_t val, void * ctx)
{
	printf("Value cleared: %ld\n", (uint64_t) val);
}

static int cmp_func(ll_value_t v1, ll_value_t v2)
{
	if (v1 < v2)
		return -1;

	return ((v1 == v2) ? 0 : 1);
}

#endif
