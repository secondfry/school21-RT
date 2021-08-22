#include "array.h"

t_byte	ptr_array_has(t_ptr_array *arr, void *data)
{
	size_t	i;

	i = 0;
	while (i < arr->used)
	{
		if (arr->data[i] == data)
			return (1);
		i++;
	}
	return (0);
}
