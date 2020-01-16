/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cud3d_raycasting.1.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/02 13:59:44 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/06 12:03:23 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"
#include "math.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	int pos;

	if (x >= 0 && x < data->map_data->dem_x && y >= 0 && y < data->map_data->dem_y)
	{
		pos = y * data->mlx_data->line_lenght + x * (data->mlx_data->bits_per_pixel / 8);
		*(unsigned int *)(data->mlx_data->mlx_addr + pos) = color;
	}
}

void	check_side(int side, int distance, t_data *data)
{
	while (side >= distance)
	{

	}
}

void find_angle(t_data *data, int distance, int start, int end)
{
	data->angles->opposite = 7 * tan(0.523598776);
	data->angles->hypotenuse = sqrt((data->angles->opposite * data->angles->opposite) + (distance + distance));
}

void	put_wall(t_data *data, int distance, int start, int end)
{
	int x;
	int y;
	int color;

	x = 0;
	y = 0;
	color = 0x000000FF;
	printf("start = %d, end = %d\n\n", start, end);
	while (x < data->map_data->dem_x)
	{
		while (y < data->map_data->dem_y)
		{
			mlx_pixel_put(data->mlx_data->mlx, data->mlx_data->mlx_win, x, y, color);
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
	if (data->map_data->pos_y == data->map_data->y)
		return ;
	distance = 0;
	while (data->map_data->map2d[y][x] != '1')
	{
		y--;
		distance++;
	}
	printf("y = %d\n", data->map_data->y);
	printf("distance = %d", distance);
	if (distance == 0)
		return ;
	start = ((data->map_data->dem_y - (data->map_data->dem_y / distance)) / 2);
	end = start + (data->map_data->dem_y / distance);
	put_wall(data, distance, start, end);
}

