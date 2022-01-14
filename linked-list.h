#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H


#ifndef VALUE_TYPE
#define VALUE_TYPE void *
#endif

typedef VALUE_TYPE ll_value_t;
typedef int (*cmp_func_t)(ll_value_t, ll_value_t);
typedef void (*consume_func_t)(ll_value_t);

typedef struct ll_node_t
{
	ll_value_t value;
	ll_node_t * next;
} ll_node_t;

typedef struct linked_list_t
{
	ll_node_t * head;
	ll_node_t * tail;

	cmp_func_t cmp;
} linked_list_t;


#ifdef __cplusplus
extern "C"
{
#endif
void ll_init(linked_list_t * ll, cmp_func_t cmp);

#ifdef __cplusplus
}
#endif

#endif
