/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_sprites.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/16 18:41:27 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/21 15:16:51 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"

t_sprite_data	*sprite_start_end(t_data *data, t_sprite_data *s_data)
{
	(*s_data).sprite_height = (int)(*data).map_data.dem_y / (*s_data).trans_y;
	if ((*s_data).sprite_height < 0)
		(*s_data).sprite_height *= -1;
	(*s_data).drawstart_y = -(*s_data).sprite_height \
	/ 2 + (*data).map_data.dem_y / 2;
	if ((*s_data).drawstart_y < 0)
		(*s_data).drawstart_y = 0;
	(*s_data).drawend_y = \
			(*s_data).sprite_height / 2 + (*data).map_data.dem_y / 2;
	if ((*s_data).drawend_y >= (*data).map_data.dem_y)
		(*s_data).drawend_y = (*data).map_data.dem_y - 1;
	(*s_data).sprite_width = (int)(*data).map_data.dem_y / (*s_data).trans_y;
	if ((*s_data).sprite_width < 0)
		(*s_data).sprite_width *= -1;
	(*s_data).drawstart_x = \
			-(*s_data).sprite_width / 2 + (*s_data).spritescreen_x;
	if ((*s_data).drawstart_x < 0)
		(*s_data).drawstart_x = 0;
	(*s_data).drawend_x = (*s_data).sprite_width / 2 + (*s_data).spritescreen_x;
	if ((*s_data).drawend_x >= (*data).map_data.dem_x)
		(*s_data).drawend_x = (*data).map_data.dem_x - 1;
	return (s_data);
}

t_sprite_data	*get_info(t_sprite_data *s_data, t_data *data, t_vs sprite)
{
	(*s_data).sprite_x = sprite.x - (*data).map_data.pos_x;
	(*s_data).sprite_y = sprite.y - (*data).map_data.pos_y;
	(*s_data).invdet = 1.0 / ((*data).map_data.plane_x * (*data).map_data.dir_y\
	- (*data).map_data.dir_x * (*data).map_data.plane_y);
	(*s_data).trans_x = (*s_data).invdet * ((*data).map_data.dir_y \
	* (*s_data).sprite_x - (*data).map_data.dir_x * (*s_data).sprite_y);
	(*s_data).trans_y = (*s_data).invdet * (-(*data).map_data.plane_y\
	* (*s_data).sprite_x + (*data).map_data.plane_x * (*s_data).sprite_y);
	(*s_data).spritescreen_x = (int)(((*data).map_data.dem_x / 2) *\
	(1 + (*s_data).trans_x / (*s_data).trans_y));
	return (s_data);
}

int				*get_order(t_data *data, int *order, double *distance)
{
	int		k;
	int		i;
	int		num;
	double	biggest;

	k = 0;
	while (k < (*data).map_data.amouth_of_sprites)
	{
		i = 0;
		biggest = 0;
		while (i < (*data).map_data.amouth_of_sprites)
		{
			if (distance[i] > biggest)
			{
				biggest = distance[i];
				num = i;
			}
			i++;
		}
		order[k] = num;
		distance[num] = 0;
		k++;
	}
	return (order);
}

int				*get_distance(t_data *data, int *order)
{
	int		i;
	double	*distance;

	distance = ft_calloc((*data).map_data.amouth_of_sprites, sizeof(double));
	if (distance == NULL)
		exit(print_error(16, 0));
	i = 0;
	while (i < (*data).map_data.amouth_of_sprites)
	{
		distance[i] = ((*data).map_data.pos_x - (*data).map_data.spr[i].x) * \
		((*data).map_data.pos_x - (*data).map_data.spr[i].x) + \
			((*data).map_data.pos_y - (*data).map_data.spr[i].y)\
		* ((*data).map_data.pos_y - (*data).map_data.spr[i].y);
		i++;
	}
	order = get_order(data, order, distance);
	free(distance);
	return (order);
}

t_data			*sprites(t_data *data)
{
	int *order;

	order = ft_calloc((*data).map_data.amouth_of_sprites, sizeof(int));
	if (order == NULL)
		exit(print_error(16, 0));
	order = get_distance(data, order);
	project_sprites(data, order);
	free(order);
	return (data);
}
