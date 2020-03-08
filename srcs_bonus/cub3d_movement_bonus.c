/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_movement_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/18 15:19:18 by nphilipp       #+#    #+#                */
/*   Updated: 2020/03/04 19:31:00 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int	life_up(t_data *data, char c)
{
	if (c == '2' && data->dda.life < 1.0)
	{
		data->dda.life += 0.01;
		return (0);
	}
	if (c == '3')
	{
		data->dda.life -= 0.01;
		return (0);
	}
	return (1);
}

void		move_forward(t_data *data)
{
	if (data->map_data.map2d[(int)(data->map_data.pos_y)]\
	[(int)(data->map_data.pos_x + (data->map_data.dir_x * 0.06))] == '0')
	{
		data->map_data.pos_x += data->map_data.dir_x * 0.04;
	}
	if (data->map_data.map2d[(int)(data->map_data.pos_y + data->map_data.dir_y\
	* 0.06)][(int)data->map_data.pos_x] == '0')
	{
		data->map_data.pos_y += data->map_data.dir_y * 0.04;
	}
	if (life_up(data, data->map_data.map2d[(int)(data->map_data.pos_y)]\
	[(int)(data->map_data.pos_x + (data->map_data.dir_x * 0.06))]))
	{
		life_up(data, data->map_data.map2d[(int)(data->map_data.pos_y\
		+ data->map_data.dir_y * 0.06)][(int)data->map_data.pos_x]);
	}
}

void		move_backwards(t_data *data)
{
	if (data->map_data.map2d[(int)(data->map_data.pos_y)]\
	[(int)(data->map_data.pos_x - (data->map_data.dir_x * 0.06))] == '0')
	{
		data->map_data.pos_x -= data->map_data.dir_x * 0.04;
	}
	if (data->map_data.map2d[(int)\
	(data->map_data.pos_y - (data->map_data.dir_y * 0.06))]\
	[(int)data->map_data.pos_x] == '0')
	{
		data->map_data.pos_y -= data->map_data.dir_y * 0.04;
	}
	if (life_up(data, data->map_data.map2d[(int)(data->map_data.pos_y)]\
	[(int)(data->map_data.pos_x - (data->map_data.dir_x * 0.06))]))
	{
		life_up(data, data->map_data.map2d[(int)(data->map_data.pos_y\
		- (data->map_data.dir_y * 0.06))][(int)data->map_data.pos_x]);
	}
}

void		move_left(t_data *data)
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
	if (life_up(data, data->map_data.map2d[(int)(data->map_data.pos_y)]\
	[(int)(data->map_data.pos_x + (data->map_data.dir_y * -1) * 0.06)]))
	{
		life_up(data, data->map_data.map2d[(int)(data->map_data.pos_y \
		+ data->map_data.dir_x * 0.06)][(int)data->map_data.pos_x]);
	}
}

void		move_right(t_data *data)
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
	if (life_up(data, (data->map_data.map2d[(int)(data->map_data.pos_y)]\
	[(int)(data->map_data.pos_x + (data->map_data.dir_y) * 0.06)])))
	{
		life_up(data, data->map_data.map2d[(int)(data->map_data.pos_y + \
	(data->map_data.dir_x * -1) * 0.06)][(int)data->map_data.pos_x]);
	}
}
