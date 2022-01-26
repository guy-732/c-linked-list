#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LL_MINIMAL
#include "../linked-list.h"
#include "utility.h"

#define LENGTH ((uint64_t) 20)
#define MAX_VAL (6)


int main()
{
	linked_list_t ll;
	uint64_t ui;
	int64_t ret;

	ll_value_t v;

	ll_init(&ll, cmp_func);

	for (ui = 0; ui < LENGTH; ++ui)
	{
		v = rand() % MAX_VAL;
		if (!ll_insert_tail(&ll, v))
			fprintf(stderr, "Failed to add value %lu (%s)\n", (uint64_t) v, strerror(errno));
	}

	v = rand() % MAX_VAL;
	printf("Removing all %lu...\n", (uint64_t) v);

	ret = ll_remove_values(&ll, v);

	printf("Removed %ld values\n", ret);

	ll_clear(&ll, clear_func);

	return 0;
}