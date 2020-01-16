/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cud3d_raycasting.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/02 13:59:44 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/10 17:16:22 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"
#include "math.h"



void	put_wall(t_data *data, int start, int end) // removed int distance
{
	int x;
	int y;
	int color;

	x = 0;
	y = 0;
	color = 0x000000FF;
	while (x < data->map_data->dem_x)
	{
		while (y < data->map_data->dem_y)
		{
			put_pixel(data, x, y, color);
			y++;
			if (y > start && y < end)
				color = 0x00FF0000;
			if (y > end)
				color = 0x0000FF00;
			if (y < start)
				color = 0x000000FF;
		}
		y = 0;
		x++;
	}
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->mlx_win, \
		data->mlx_data->mlx_img, 0, 0);
}

void	ray_casting_n(t_data *data)
{
	int x;
	int y;
	int end;
	int start;
	int distance;

	y = data->map_data->pos_y;
	x = data->map_data->pos_x;
	data->mlx_data->mlx_img = mlx_new_image(data->mlx_data->mlx,\
		data->map_data->dem_x, data->map_data->dem_x);
	data->mlx_data->mlx_addr = mlx_get_data_addr(data->mlx_data->mlx_img,\
		&data->mlx_data->bits_per_pixel, &data->mlx_data->line_lenght,\
			&data->mlx_data->endian);
	if (data->map_data->pos_y == data->map_data->y)
		return ;
	distance = 0;
	while (data->map_data->map2d[y][x] != '1')
	{
		y--;
		distance++;
	}
	if (distance == 0)
		return ;
	start = ((data->map_data->dem_y - (data->map_data->dem_y / distance)) / 2);
	end = start + (data->map_data->dem_y / distance);
	put_wall(data, start, end); //removed int distance
}

