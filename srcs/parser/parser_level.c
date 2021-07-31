#include "parser.h"

t_level	*level_new(void)
{
	t_level	*ret;

	ret = (t_level *)malloc(sizeof(t_level));
	ft_ptr_check(ret, ERR_MEM_MSG, 0);
	ret->key = (void *)0;
	ret->type = LTYPE_UNSET;
	ret->parent = (void *)0;
	ret->value = (void *)0;
	ret->data = (void *)0;
	ret->offset = -1;
	ret->child_offset = -1;
	return (ret);
}
