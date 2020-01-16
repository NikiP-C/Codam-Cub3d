/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cud3draycasting2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 17:13:40 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/10 11:20:37 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"

t_data	*field_vision(t_data *data)
{
	int i;
	int j;

	data->vision->distance = 0;
	j = data->map_data->pos_y;
	i = data->map_data->pos_x;
	while (data->map_data->map2d[j][i] != '1')
	{
		i += data->map_data->dir_x;
		j += data->map_data->dir_y;
		data->vision->distance++;
	}
	data->vision->opposite = tan(0.523598776) * data->vision->distance;
	if (j == data->map_data->pos_y)
	{
		data->vision->start_x = i;
		data->vision->end_x = i;
		data->vision->start_y = data->map_data->pos_y + data->vision->opposite;
		data->vision->end_y = data->map_data->pos_y - data->vision->opposite;
	}
	if (i == data->map_data->pos_x)
	{
		data->vision->start_x = data->map_data->pos_x - data->vision->opposite;
		data->vision->end_x = data->map_data->pos_x + data->vision->opposite;
		data->vision->start_y = j;
		data->vision->end_y = j;
	}
	data->vision->step_y = (data->vision->start_y - data->map_data->pos_y) / 20;
	data->vision->step_x = (data->vision->start_x - data->map_data->pos_x) / 20;
	return (data);
}

void	found_collison(int i, int j, t_data *data)
{
	int size;
	int std_wall_size;

	std_wall_size = data->map_data->dem_y / 3;
	if (data->map_data->dir_x == 0)
		size = data->vision->distance / j;
	if (data->map_data->dir_x == 0)
		size = data->vision->distance / i;
}

void	tracing_ray(t_data *data)
{
	double i;
	double j;

	j = data->map_data->pos_y;
	i = data->map_data->pos_x;
	while (data->map_data->map2d[(int)j][(int)i] != 1)
	{
		j += data->vision->step_y;
		i += data->vision->step_x;
	}
	found_collison(i, j, data);
}

int		making_of_a_ray(t_data *data)
{
	int i;

	i = 0;
	while (i < data->map_data->dem_x)
	{
		data = field_vision(data);
		tracing_ray(data);
	}
}
