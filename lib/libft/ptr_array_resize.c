#include "libft.h"
#include "array.h"

t_ptr_array	*ptr_array_resize(t_ptr_array *arr, size_t len)
{
	t_ptr_array	*ret;

	if (!arr)
		return ((void *)0);
	len = len + sizeof(long) - len % sizeof(long);
	ret = ptr_array_new(len);
	if (!ret)
		return ((void *)0);
	ft_memcpy(ret->data, arr->data, arr->used);
	ret->used = arr->used;
	ft_memdel((void **)&arr);
	return (ret);
}
