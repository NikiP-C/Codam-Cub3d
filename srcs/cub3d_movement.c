/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_movement.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/18 15:19:18 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/22 19:50:36 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_data		*move_forward(t_data *data)
{
	if (data->map_data.map2d[(int)(data->map_data.pos_y)]\
	[(int)(data->map_data.pos_x + data->map_data.dir_x * 0.06)] == '0')
	{
		data->map_data.pos_x += data->map_data.dir_x * 0.04;
	}
	if (data->map_data.map2d[(int)(data->map_data.pos_y + data->map_data.dir_y\
	* 0.06)][(int)data->map_data.pos_x] == '0')
	{
		data->map_data.pos_y += data->map_data.dir_y * 0.04;
	}
	return (data);
}

t_data		*move_backwards(t_data *data)
{
	if (data->map_data.map2d[(int)(data->map_data.pos_y)]\
	[(int)(data->map_data.pos_x - data->map_data.dir_x * 0.06)] == '0')
	{
		data->map_data.pos_x -= data->map_data.dir_x * 0.04;
	}
	if (data->map_data.map2d[(int)\
	(data->map_data.pos_y - data->map_data.dir_y * 0.06)]\
	[(int)data->map_data.pos_x] == '0')
	{
		data->map_data.pos_y -= data->map_data.dir_y * 0.04;
	}
	return (data);
}

t_data		*move_left(t_data *data)
{
	if (data->map_data.map2d[(int)(data->map_data.pos_y)][(int)\
	(data->map_data.pos_x + (data->map_data.dir_y * -1) * 0.06)] == '0')
	{
		data->map_data.pos_x += (data->map_data.dir_y * -1) * 0.04;
	}
	if (data->map_data.map2d[(int)(data->map_data.pos_y + \
	(data->map_data.dir_x) * 0.06)][(int)data->map_data.pos_x] == '0')
	{
		data->map_data.pos_y += (data->map_data.dir_x) * 0.04;
	}
	return (data);
}

t_data		*move_right(t_data *data)
{
	if (data->map_data.map2d[(int)(data->map_data.pos_y)][(int)\
	(data->map_data.pos_x + (data->map_data.dir_y) * 0.06)] == '0')
	{
		data->map_data.pos_x += (data->map_data.dir_y) * 0.04;
	}
	if (data->map_data.map2d[(int)\
	(data->map_data.pos_y + (data->map_data.dir_x * -1) * 0.06)]\
		[(int)data->map_data.pos_y] == '0')
	{
		data->map_data.pos_y += (data->map_data.dir_x * -1) * 0.04;
	}
	return (data);
}
