// #irndef VALIDATOR_H
// # define VALIDATOR_H

// # include "parser.h"

// /**
//  *	Коды ошибок валидатора
//  */
// # define ERR_VALIDATOR_ROOT_NODES "[validator] Root parts of configuration expected to be nodes."

// # define ERR_VALIDATOR_LIGHT_INCOMPLETE "[validator] Light configuration is incomplete."
// # define ERR_VALIDATOR_LIGHT_POINT_LIST "[validator] Point lights configuration members expected to list nodes."
// # define ERR_VALIDATOR_LIGHT_POINT_INVALID "[validator] Point light configuration is invalid."
// # define ERR_VALIDATOR_LIGHT_DIRECTIONAL_LIST "[validator] Directional lights configuration members expected to list nodes."
// # define ERR_VALIDATOR_LIGHT_DIRECTIONAL_INVALID "[validator] Directional light configuration is invalid."

// # define ERR_VALIDATOR_SPHERE_INCOMPLETE "[validator] Sphere configuration is incomplete."

// void		validate(t_rtv *rtv, t_level *root);
// //	Валидация света
// t_byte		validate_light(t_rtv *rtv, t_level *root);
// t_byte		validate_light_ambient(t_rtv *rtv, t_level *root);
// t_byte		validate_light_point_one_position(t_rtv *rtv, t_level *root, t_byte idx);
// t_byte		validate_light_point_one_intensity(t_rtv *rtv, t_level *root, t_byte idx);
// t_byte		validate_light_point_one(t_rtv *rtv, t_level *root, t_byte idx);
// t_byte		validate_light_point(t_rtv *rtv, t_level *root);
// t_byte		validate_light_directional_one_directional(t_rtv *rtv, t_level *root, t_byte idx);
// t_byte		validate_light_directional_one_intensity(t_rtv *rtv, t_level *root, t_byte idx);
// t_byte		validate_light_directional_one(t_rtv *rtv, t_level *root, t_byte idx);
// t_byte		validate_light_directional(t_rtv *rtv, t_level *root);
// //	Валидация сферы
// t_byte		validate_sphere(t_rtv *rtv, t_level *root);

// #endif
