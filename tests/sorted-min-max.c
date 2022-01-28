#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#include "../linked-list.h"
#include "utility.h"

#define LENGTH ((uint64_t) 20)
#define MAX_VAL (2000)


#define BOOL_STR(b) ((b) ? "true" : "false")


int main()
{
	linked_list_t ll1, ll2;
	uint64_t ui;
	int64_t i_min, i_max;
	ll_value_t v, min, max;

	ll_init(&ll1, cmp_func);
	ll_init(&ll2, cmp_func);

	for (ui = 0; ui < LENGTH; ++ui)
	{
		v = (ll_value_t) (uint64_t) (rand() % MAX_VAL);
		if (!ll_insert_tail(&ll1, v))
			fprintf(stderr, "Failed to add value %lu in unsorted list (%s)\n", (uint64_t) v, strerror(errno));

		if (!ll_insert_sorted(&ll2, v))
			fprintf(stderr, "Failed to add value %lu in sorted list (%s)\n", (uint64_t) v, strerror(errno));
	}

	printf("\"unsorted\" list is sorted (maybe, it's random)? %s\n", BOOL_STR(ll_is_sorted(&ll1)));
	printf("sorted list is sorted (should be)? %s\n\n", BOOL_STR(ll_is_sorted(&ll2)));

	printf("Unsorted list\n");
	if (ll_min_max(&ll1, &min, &i_min, &max, &i_max))
	{
		printf("\tMinimum value: %lu at index %ld\n",
		(uint64_t) min, i_min);
		printf("\tMaximum value: %lu at index %ld\n",
		(uint64_t) max, i_max);
	}
	else
		fprintf(stderr, "\tFailed to get min-max (%s)\n", strerror(errno));

	printf("Sorted list\n");
	if (ll_min_max(&ll2, &min, &i_min, &max, &i_max))
	{
		printf("\tMinimum value: %lu at index %ld\n",
		(uint64_t) min, i_min);
		printf("\tMaximum value: %lu at index %ld\n",
		(uint64_t) max, i_max);
	}
	else
		fprintf(stderr, "\tFailed to get min-max (%s)\n", strerror(errno));


	printf("\nClearing unsorted list...\n");
	ll_clear(&ll1, clear_func, NULL);
	printf("\nClearing sorted list...\n");
	ll_clear(&ll2, clear_func, NULL);

	return 0;
}
