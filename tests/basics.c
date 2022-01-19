#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "../linked-list.h"


static void clear_func(ll_value_t val)
{
	printf("Value cleared: %ld\n", (uint64_t) val);
}

static int cmp_func(ll_value_t v1, ll_value_t v2)
{
	if (v1 < v2)
		return -1;

	return ((v1 == v2) ? 0 : 1);
}


int main()
{
	linked_list_t ll;
	uint64_t i;
	ll_init(&ll, cmp_func);

	for (i = 0; i < 5; ++i)
	{
		if (!ll_insert_tail(&ll, (ll_value_t) i))
			fprintf(stderr, "Failed to add value %zu (%s)\n", i, strerror(errno));
	}

	printf("Length: %zu\n", ll_len(&ll));

	for (i = 56; i > 52; --i)
	{
		if (!ll_insert_head(&ll, (ll_value_t) i))
			fprintf(stderr, "Failed to add value %zu (%s)\n", i, strerror(errno));
	}

	printf("Length: %zu\n", ll_len(&ll));

	ll_clear(&ll, clear_func);

	return 0;
}
