#include <stdio.h>
#include <errno.h>
#include <string.h>

#define LL_MINIMAL
#include "../linked-list.h"
#include "utility.h"


#define LENGTH ((uint64_t) 20)


int main()
{
	linked_list_t ll;
	uint64_t ui;
	int64_t i;

	ll_value_t v1, v2;

	ll_init(&ll, cmp_func);

	for (ui = 0; ui < LENGTH; ++ui)
	{
		if (!ll_insert_tail(&ll, (ll_value_t) ui))
			fprintf(stderr, "Failed to add value %lu (%s)\n", ui, strerror(errno));
	}

	if ((ui = ll_len(&ll)) != LENGTH)
		fprintf(stderr, "Incorrect length: expected %lu, got %lu\n", LENGTH, ui);

	for (i = LENGTH - 1; i > -1; --i)
	{
		errno = 0;
		if ((!ll_get_item(&ll, i, &v1)) || (!ll_get_item(&ll, i - ((int64_t) LENGTH), &v2)))
		{
			fprintf(stderr, "Failed to get value at index %ld (errno: %s)\n", i, strerror(errno));
			continue;
		}

		if (v1 != v2 || ((ll_value_t) i) != v1)
		{
			fprintf(stderr,
			"Values different from what was expected, got %lu & %lu, expected %ld\n",
			(uint64_t) v1, (uint64_t) v2, i);
		}
	}

	for (i = 0; i < ((int64_t) LENGTH); ++i)
	{
		errno = 0;
		if (!ll_set_item(&ll, i, (ll_value_t)(i + 1)))
		{
			fprintf(stderr, "Failed to set value at index %ld (errno: %s)\n", i, strerror(errno));
		}
	}

	ll_clear(&ll, clear_func);
	return 0;
}