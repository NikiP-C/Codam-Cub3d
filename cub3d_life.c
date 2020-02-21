/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_life.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 12:38:55 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/20 12:46:17 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"

void	put_healthbar(t_data *data)
{
	int end[2];
	int y;
	int x;
	int green;

	end[0] = (*data).map_data.dem_y / 50 * 48;
	end[1] = (*data).map_data.dem_x / 6 * 5;
	y = (*data).map_data.dem_y / 50 * 47;
	green = ((double)(end[1] - (*data).map_data.dem_x / 6)\
	* (*data).dda.life) + (*data).map_data.dem_x / 6;
	while (y < end[0])
	{
		x = (*data).map_data.dem_x / 6;
		while (x != end[1])
		{
			if (x < green)
				put_pixel(data, x, y, 0x0000FF00);
			else
				put_pixel(data, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
}

void	death_screen(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < (*data).map_data.dem_y)
	{
		x = 0;
		while (x < (*data).map_data.dem_x)
		{
			put_pixel(data, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}
