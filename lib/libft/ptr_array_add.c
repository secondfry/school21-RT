#include "array.h"

t_ptr_array	*ptr_array_add(t_ptr_array *arr, void *data)
{
	if (arr->size == arr->used)
		arr = ptr_array_resize(arr, arr->size);
	arr->data[arr->used] = data;
	arr->used++;
	return (arr);
}
