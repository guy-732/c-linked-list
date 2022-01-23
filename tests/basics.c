#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "../linked-list.h"
#include "utility.h"


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
