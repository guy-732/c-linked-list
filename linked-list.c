#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "linked-list.h"


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
