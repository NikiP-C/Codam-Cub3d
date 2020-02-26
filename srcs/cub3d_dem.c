/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_dem.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 12:16:55 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/26 16:34:38 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_dem_num(int fd, char *c)
{
	int num;
	int neg;

	neg = 1;
	num = 0;
	while (*c == ' ')
		read(fd, c, 1);
	if (*c == '-')
	{
		neg = -1;
		read(fd, c, 1);
	}
	if (*c >= '0' && *c <= '9')
	{
		while (*c >= '0' && *c <= '9')
		{
			num = num * 10 + (*c - '0');
			read(fd, c, 1);
		}
		return (num * neg);
	}
	return (0);
}

void		get_dem(int fd, char c, t_data *data)
{
	int max_x;
	int max_y;

	mlx_get_screen_size(data->mlx_data.mlx, &max_x, &max_y);
	(*data).map_data.dem_x = get_dem_num(fd, &c);
	if ((*data).map_data.dem_x <= 0)
		exit(print_error(5, 0));
	(*data).map_data.dem_y = get_dem_num(fd, &c);
	if ((*data).map_data.dem_y <= 0)
		exit(print_error(5, 0));
	if (data->safe == 0)
	{
		if ((*data).map_data.dem_y > max_y)
			(*data).map_data.dem_y = max_y;
		if ((*data).map_data.dem_x > max_x)
			(*data).map_data.dem_x = max_x;
	}
	while (c == ' ')
		read(fd, &c, 1);
	if (c != '\n')
		exit(print_error(3, c));
}
