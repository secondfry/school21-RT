#include "loop_hook.h"

static void	invalidate_sphere_vectors(t_rtv *rtv, t_sphere sphere)
{
	const t_vector_4	CO = vector_sub(
		rtv->camera_position,
		sphere.vectors[VCTR_SPHERE_C]
	);

	vector_set(sphere.vectors + VCTR_SPHERE_CO, &CO);
}

static void	invalidate_spheres_vectors(t_rtv *rtv)
{
	t_byte	i;

	i = 0;
	while (i < MAX_SPHERES)
	{
		invalidate_sphere_vectors(rtv, rtv->spheres[i]);
		i++;
	}
}

void	loop_invalidate_position(t_rtv *rtv)
{
	if (!(rtv->flags & FLAG_INVALIDATE_POSITION))
		return ;
	rtv->flags -= FLAG_INVALIDATE_POSITION;
	invalidate_spheres_vectors(rtv);
	rtv->flags |= FLAG_REDRAW;
}

void	loop_invalidate_rotation(t_rtv *rtv)
{
	t_quaterion	rotator;

	if (!(rtv->flags & FLAG_INVALIDATE_ROTATION))
		return ;
	rtv->flags -= FLAG_INVALIDATE_ROTATION;
	rotator = quaternion_new(\
		rtv->camera_angles.x * M_PI_F / 180, \
		rtv->camera_angles.y * M_PI_F / 180, \
		rtv->camera_angles.z * M_PI_F / 180 \
	);
	free(rtv->camera_rotation);
	rtv->camera_rotation = quaternion_to_matrix(rotator);
	free(rotator);
	rtv->flags |= FLAG_REDRAW;
}
