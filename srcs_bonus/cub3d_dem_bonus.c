/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_dem_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 12:16:55 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/25 16:31:21 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int	get_dem_num(int fd, char *c)
{
	int num;
	int neg;

	neg = 1;
	num = 0;
	read(fd, c, 1);
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
	read(fd, &c, 1);
	(*data).map_data.dem_x = get_dem_num(fd, &c);
	if ((*data).map_data.dem_x > 2560)
		(*data).map_data.dem_x = 2560;
	if ((*data).map_data.dem_x <= 0)
		exit(print_error(5, 0));
	(*data).map_data.dem_y = get_dem_num(fd, &c);
	if ((*data).map_data.dem_y <= 0)
		exit(print_error(5, 0));
	if ((*data).map_data.dem_y > 1440)
		(*data).map_data.dem_y = 1440;
	while (c == ' ')
		read(fd, &c, 1);
	if (c != '\n')
		exit(print_error(3, c));
}
