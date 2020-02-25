/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_get_textures.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 12:01:52 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/25 15:37:49 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
		(*data).textures.floor = get_color(fd, new);
		(*err).floor = 1;
	}
	else
	{
		(*data).textures.clg = get_color(fd, new);
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

