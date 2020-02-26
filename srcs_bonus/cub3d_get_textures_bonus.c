/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_get_textures_bonus.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 12:01:52 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/26 15:51:18 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static int			get_num(int fd, char *c)
{
	int num;
	int neg;

	num = 0;
	neg = 1;
	if (*c == ' ')
		read(fd, c, 1);
	if (*c == '-')
	{
		neg = -1;
		read(fd, c, 1);
	}
	while (*c >= '0' && *c <= '9')
	{
		num = num * 10 + (*c - '0');
		read(fd, c, 1);
	}
	while (*c == ' ')
		read(fd, c, 1);
	return (num * neg);
}

static int			get_color(int fd, char c)
{
	int r;
	int g;
	int b;

	r = get_num(fd, &c);
	if (c != ',')
		exit(print_error(3, c));
	read(fd, &c, 1);
	g = get_num(fd, &c);
	if (c != ',')
		exit(print_error(3, c));
	read(fd, &c, 1);
	b = get_num(fd, &c);
	if (c != '\n')
		exit(print_error(3, c));
	if (r > 255 || g > 255 || b > 255 || b < 0 || g < 0 || r < 0)
		exit(print_error(10, 0));
	return ((0 << 24 | r << 16 | g << 8 | b));
}

static void			floor_get(t_data *data, char b, int fd, t_error *err)
{
	while (b == ' ')
		read(fd, &b, 1);
	if ((*err).clg == 1)
		exit(print_error(19, 0));
	if ((b >= '0' && b <= '9') || b == '-')
		(*data).textures.floor = get_color(fd, b);
	else
		(*data).textures.floor_tex = get_path(b, fd, data, &((*err).clg));
	(*err).floor = 1;
}

static void			clg_get(t_data *data, char b, int fd, t_error *err)
{
	while (b == ' ')
		read(fd, &b, 1);
	if ((*err).clg == 1)
		exit(print_error(19, 0));
	if ((b >= '0' && b <= '9') || b == '-')
		(*data).textures.clg = get_color(fd, b);
	else
		(*data).textures.clg_tex = get_path(b, fd, data, &((*err).clg));
	(*err).clg = 1;
}

void				get_textures(t_data *data, int fd, char c, t_error *error)
{
	char b;

	read(fd, &b, 1);
	if (c == 'R')
		get_dem(fd, b, data);
	if (c == 'F')
		floor_get(data, b, fd, error);
	if (c == 'C')
		clg_get(data, b, fd, error);
	else if (c == 'S' && b != 'O' && b != '2')
		(*data).textures.sprite_1 = get_path(b, fd, data, &(*error).sprite1);
	else if (c == 'S' && b != 'O')
		(*data).textures.sprite_2 = get_path(' ', fd, data, &(*error).sprite2);
	else if (c == 'N' && b == 'O')
		(*data).textures.north = get_path(' ', fd, data, &(*error).north);
	else if (c == 'S' && b == 'O')
		(*data).textures.south = get_path(' ', fd, data, &(*error).south);
	else if (c == 'E' && b == 'A')
		(*data).textures.east = get_path(' ', fd, data, &(*error).east);
	else if (c == 'W' && b == 'E')
		(*data).textures.west = get_path(' ', fd, data, &(*error).west);
}
