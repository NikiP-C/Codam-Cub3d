/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_get_textures_bonus.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 12:01:52 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/25 15:38:38 by nphilipp      ########   odam.nl         */
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

static void			clg_floor(t_data *data, char c, int fd, t_error *err)
{
	int new;

	new = c;
	read(fd, &new, 1);
	while (new == ' ')
		read(fd, &new, 1);
	if (((*err).floor == 1 && c == 'F') || ((*err).clg == 1 && c == 'C'))
		exit(error_double(c, 1));
	if (c == 'F')
	{
		if ((new >= '0' && new <= '9') || new == '-')
			(*data).textures.floor = get_color(fd, new);
		else
			(*data).textures.floor_tex = get_path(new, fd, data, &(*err).floor);
		(*err).floor = 1;
	}
	else
	{
		if ((new >= '0' && new <= '9') || new == '-')
			(*data).textures.clg = get_color(fd, new);
		else
			(*data).textures.clg_tex = get_path(new, fd, data, &((*err).clg));
		(*err).clg = 1;
	}
}

void				get_textures(t_data *data, int fd, char c, t_error *error)
{
	char b;

	read(fd, &b, 1);
	if (c == 'R')
		get_dem(fd, c, data);
	if (c == 'F' || c == 'C')
		clg_floor(data, c, fd, error);
	else if (c == 'S' && b != 'O' && b != '2')
		(*data).textures.sprite_1 = get_path(' ', fd, data, &(*error).sprite1);
	else if (c == 'S' && b != 'O')
		(*data).textures.sprite_2 = get_path(' ', fd, data, &(*error).sprite2);
	else if ((c == 'N' && (*error).north) || (c == 'S' && (*error).south) \
				|| (c == 'E' && (*error).east) || (c == 'W' && (*error).west))
		exit(print_error(c, 1));
	else if (c == 'N' && b == 'O')
		(*data).textures.north = get_path(' ', fd, data, &(*error).north);
	else if (c == 'S' && b == 'O')
		(*data).textures.south = get_path(' ', fd, data, &(*error).south);
	else if (c == 'E' && b == 'A')
		(*data).textures.east = get_path(' ', fd, data, &(*error).east);
	else if (c == 'W' && b == 'E')
		(*data).textures.west = get_path(' ', fd, data, &(*error).west);
}
