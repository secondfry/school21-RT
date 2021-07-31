#include "intersection.h"

t_intersection	intersection_closest(t_rtv *rtv, t_intersect_params *params)
{
	t_intersection	results[FIGURES];
	t_intersection	res;

	res.distance = 1.0 / 0.0;
	results[ISPHERE] = intersection_sphere_closest(rtv, params);
	if (results[ISPHERE].distance < res.distance)
		res = results[ISPHERE];
	results[IPLANE] = intersection_plane_closest(rtv, params);
	if (results[IPLANE].distance < res.distance)
		res = results[IPLANE];
	results[ICYLINDER] = intersection_cylinder_closest(rtv, params);
	if (results[ICYLINDER].distance < res.distance)
		res = results[ICYLINDER];
	results[ICONE] = intersection_cone_closest(rtv, params);
	if (results[ICONE].distance < res.distance)
		res = results[ICONE];
	return (res);
}
