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

	ll_value_t v;

	ll_init(&ll, cmp_func);

	for (ui = 0; ui < LENGTH; ++ui)
	{
		if (!ll_insert_tail(&ll, (ll_value_t) ui))
			fprintf(stderr, "Failed to add value %lu (%s)\n", ui, strerror(errno));
	}

	if ((ui = ll_len(&ll)) != LENGTH)
		fprintf(stderr, "Incorrect length: expected %lu, got %lu\n", LENGTH, ui);

	if (!ll_remove_item(&ll, ui / 2, &v))
	{
		fprintf(stderr, "Failed to remove item at index %lu (errno: %s)\n", ui / 2, strerror(errno));
		v = (ll_value_t) -1;
		printf("Set `v` to %lu to avoid messing with the next part\n", (uint64_t) v);
	}
	else
	{
		printf("Removed value %lu from linked list\n", (uint64_t) v);
	}

	if (!ll_remove_head(&ll, NULL) || !ll_remove_tail(&ll, NULL))
	{
		fprintf(stderr, "Failed to remove head and/or tail (errno: %s)\n", strerror(errno));
	}

	for (ui = 1; ui < LENGTH - 1; ++ui)
	{
		errno = 0;
		if ((!ll_index_of(&ll, (ll_value_t) ui, &i)))
		{
			if (((ll_value_t) ui) != v)
				fprintf(stderr, "Failed to get index for value %lu (errno: %s)\n", ui, strerror(errno));
			else
				printf("Value %lu not in linked list\n", ui);
		}
		else
		{
			printf("Index of value %lu: %ld\n", ui, i);
		}
	}

	ll_clear(&ll, clear_func);
	return 0;
}
