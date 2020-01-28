/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_movement.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/18 15:19:18 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/27 20:37:59 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"

int		move_forward(t_data *data)
{
	if (data->map_data->map2d[(int)(data->map_data->pos_y)]\
		[(int)(data->map_data->pos_x + data->map_data->dir_x * 0.2)] == '0')
	{
		data->map_data->pos_x += data->map_data->dir_x * 0.2;
	}
	if (data->map_data->map2d[(int)\
	(data->map_data->pos_y + data->map_data->dir_y * 0.2)]\
		[(int)data->map_data->pos_x] == '0')
	{
		data->map_data->pos_y += data->map_data->dir_y * 0.2;
	}
	make_frame(data);
	return (0);
}

int		move_backwards(t_data *data)
{
	printf("move\n");
	if (data->map_data->map2d[(int)(data->map_data->pos_y)]\
		[(int)(data->map_data->pos_x - data->map_data->dir_x * 0.2)] == '0')
	{
		data->map_data->pos_x -= data->map_data->dir_x * 0.2;
	}
	if (data->map_data->map2d\
	[(int)(data->map_data->pos_y - data->map_data->dir_y * 0.2)]\
		[(int)data->map_data->pos_x] == '0')
	{
		data->map_data->pos_y -= data->map_data->dir_y * 0.2;
	}
	printf("move\n");
	make_frame(data);
	return (0);
}

int		move_left(t_data *data)
{
	if (data->map_data->map2d[(int)(data->map_data->pos_y)]\
		[(int)(data->map_data->pos_x + (data->map_data->dir_y * -1) * 0.2)] == '0')
	{
		data->map_data->pos_x += (data->map_data->dir_y * -1) * 0.2;
	}
	if (data->map_data->map2d[(int)\
	(data->map_data->pos_y + (data->map_data->dir_x) * 0.2)]\
		[(int)data->map_data->pos_x] == '0')
	{
		data->map_data->pos_y += (data->map_data->dir_x) * 0.2;
	}
	make_frame(data);
	return (0);
}

int		move_right(t_data *data)
{
	if (data->map_data->map2d[(int)(data->map_data->pos_y)]\
		[(int)(data->map_data->pos_x + (data->map_data->dir_y) * 0.2)] == '0')
	{
		data->map_data->pos_x += (data->map_data->dir_y) * 0.2;
	}
	if (data->map_data->map2d[(int)\
	(data->map_data->pos_y + (data->map_data->dir_x * -1) * 0.2)]\
		[(int)data->map_data->pos_y] == '0')
	{
		data->map_data->pos_y += (data->map_data->dir_x * -1) * 0.2;
	}
	make_frame(data);
	return (0);
}

int		turn_left(t_data *data)
{
	double old_dirx;
	double old_planex;

	old_dirx = data->map_data->dir_x;
	old_planex = data->map_data->plane_x;
	data->map_data->dir_x = data->map_data->dir_x \
	* cos(0.1) - data->map_data->dir_y * sin(-0.1);
	data->map_data->dir_y = old_dirx * sin(-0.1) + \
	data->map_data->dir_y * cos(-0.1);
	data->map_data->plane_x = old_planex * cos(-0.1) - \
	data->map_data->plane_y * sin(-0.1);
	data->map_data->plane_y = old_planex * sin(-0.1) + \
	data->map_data->plane_y * cos(-0.1);
	make_frame(data);
	return (0);
}

int		turn_right(t_data *data)
{
	double old_dirx;
	double old_planex;

	old_dirx = data->map_data->dir_x;
	old_planex = data->map_data->plane_x;
	data->map_data->dir_x = data->map_data->dir_x * \
	cos(-0.1) - data->map_data->dir_y * sin(0.1);
	data->map_data->dir_y = old_dirx * sin(0.1) + \
	data->map_data->dir_y * cos(0.1);
	data->map_data->plane_x = old_planex * cos(0.1) - \
	data->map_data->plane_y * sin(0.1);
	data->map_data->plane_y = old_planex * sin(0.1) + \
	data->map_data->plane_y * cos(0.1);
	make_frame(data);
	return (0);
}