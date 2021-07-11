#include "vector.h"

t_vector_4	vector_new(float x, float y, float z, float w)
{
	return ((t_vector_4){x, y, z, w});
}

t_vector_4	vector_sub(t_vector_4 a, t_vector_4 b)
{
	return ((t_vector_4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w});
}

t_vector_4	vector_add(t_vector_4 a, t_vector_4 b)
{
	return ((t_vector_4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w});
}

t_vector_4	vector_mult(t_vector_4 a, float k)
{
	return ((t_vector_4){a.x * k, a.y * k, a.z * k, a.w * k});
}
