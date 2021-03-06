/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_movement.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/18 15:19:18 by nphilipp       #+#    #+#                */
/*   Updated: 2020/03/05 15:51:19 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_forward(t_data *data)
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
}

void	move_backwards(t_data *data)
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
}

void	move_left(t_data *data)
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
}

void	move_right(t_data *data)
{
	if (data->map_data.map2d[(int)(data->map_data.pos_y)][(int)\
	(data->map_data.pos_x + (data->map_data.dir_y) * 0.06)] == '0')
	{
		data->map_data.pos_x += (data->map_data.dir_y) * 0.04;
	}
	if (data->map_data.map2d[(int)(data->map_data.pos_y + \
	(data->map_data.dir_x * -1) * 0.06)][(int)data->map_data.pos_x] == '0')
	{
		data->map_data.pos_y += (data->map_data.dir_x * -1) * 0.04;
	}
}
