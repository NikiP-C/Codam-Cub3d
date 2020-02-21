/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_movement.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/18 15:19:18 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/20 12:45:13 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"

static int	life_up(t_data *data, char c)
{
	if (c == '2' && (*data).dda.life < 1.0)
	{
		(*data).dda.life += 0.01;
		return (0);
	}
	if (c == '3')
	{
		(*data).dda.life -= 0.01;
		return (0);
	}
	return (1);
}

t_data		*move_forward(t_data *data)
{
	if ((*data).map_data.map2d[(int)((*data).map_data.pos_y)]\
		[(int)((*data).map_data.pos_x + (*data).map_data.dir_x * 0.04)] == '0')
	{
		(*data).map_data.pos_x += (*data).map_data.dir_x * 0.04;
	}
	if ((*data).map_data.map2d[(int)\
	((*data).map_data.pos_y + (*data).map_data.dir_y * 0.04)]\
		[(int)(*data).map_data.pos_x] == '0')
	{
		(*data).map_data.pos_y += (*data).map_data.dir_y * 0.04;
	}
	if (life_up(data, (*data).map_data.map2d[(int)((*data).map_data.pos_y)]\
	[(int)((*data).map_data.pos_x + (*data).map_data.dir_x * 0.04)]))
	{
		life_up(data, (*data).map_data.map2d[(int)((*data).map_data.pos_y\
		+ (*data).map_data.dir_y * 0.04)][(int)(*data).map_data.pos_x]);
	}
	return (data);
}

t_data		*move_backwards(t_data *data)
{
	if ((*data).map_data.map2d[(int)((*data).map_data.pos_y)]\
		[(int)((*data).map_data.pos_x - (*data).map_data.dir_x * 0.04)] == '0')
	{
		(*data).map_data.pos_x -= (*data).map_data.dir_x * 0.04;
	}
	if ((*data).map_data.map2d[(int)\
	((*data).map_data.pos_y - (*data).map_data.dir_y * 0.04)]\
		[(int)(*data).map_data.pos_x] == '0')
	{
		(*data).map_data.pos_y -= (*data).map_data.dir_y * 0.04;
	}
	if (life_up(data, (*data).map_data.map2d[(int)((*data).map_data.pos_y)]\
		[(int)((*data).map_data.pos_x - (*data).map_data.dir_x * 0.04)]))
	{
		life_up(data, (*data).map_data.map2d[(int)((*data).map_data.pos_y\
		- (*data).map_data.dir_y * 0.04)][(int)(*data).map_data.pos_x]);
	}
	return (data);
}

t_data		*move_left(t_data *data)
{
	if ((*data).map_data.map2d[(int)((*data).map_data.pos_y)]\
		[(int)((*data).map_data.pos_x + \
				((*data).map_data.dir_y * -1) * 0.04)] == '0')
	{
		(*data).map_data.pos_x += ((*data).map_data.dir_y * -1) * 0.04;
	}
	if ((*data).map_data.map2d[(int)\
	((*data).map_data.pos_y + ((*data).map_data.dir_x) * 0.04)]\
		[(int)(*data).map_data.pos_x] == '0')
	{
		(*data).map_data.pos_y += ((*data).map_data.dir_x) * 0.04;
	}
	if (life_up(data, (*data).map_data.map2d[(int)((*data).map_data.pos_y)]\
	[(int)((*data).map_data.pos_x + ((*data).map_data.dir_y * -1) * 0.04)]))
	{
		life_up(data, (*data).map_data.map2d[(int)((*data).map_data.pos_y \
		+ ((*data).map_data.dir_x) * 0.04)][(int)(*data).map_data.pos_x]);
	}
	return (data);
}

t_data		*move_right(t_data *data)
{
	if ((*data).map_data.map2d[(int)((*data).map_data.pos_y)][(int)\
	((*data).map_data.pos_x + ((*data).map_data.dir_y) * 0.04)] == '0')
	{
		(*data).map_data.pos_x += ((*data).map_data.dir_y) * 0.04;
	}
	if ((*data).map_data.map2d[(int)\
	((*data).map_data.pos_y + ((*data).map_data.dir_x * -1) * 0.04)]\
		[(int)(*data).map_data.pos_y] == '0')
	{
		(*data).map_data.pos_y += ((*data).map_data.dir_x * -1) * 0.04;
	}
	if (life_up(data, ((*data).map_data.map2d[(int)((*data).map_data.pos_y)]\
		[(int)((*data).map_data.pos_x + ((*data).map_data.dir_y) * 0.04)])))
	{
		life_up(data, (*data).map_data.map2d[(int)((*data).map_data.pos_y +\
		((*data).map_data.dir_x * -1) * 0.04)][(int)(*data).map_data.pos_y]);
	}
	return (data);
}
