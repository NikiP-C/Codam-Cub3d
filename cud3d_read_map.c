/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cud3d_read_map.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 13:59:09 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/01 20:42:56 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"

t_texture		*get_path(char b, int fd, t_data *data)
{
	char		*str;
	int			i;
	t_texture	*texture;

	i = 0;
	texture = malloc(sizeof(t_texture));
	str = malloc(50);
	read(fd, &b, 1);
	while (b == ' ')
		read(fd, &b, 1);
	while (b != '\n' && b != 0 && b != ' ')
	{
		str[i] = b;
		i++;
		read(fd, &b, 1);
	}
	str[i] = 0;
	texture->img = mlx_png_file_to_image(data->mlx_data->mlx,\
	str, &texture->width, &texture->height);
	texture->img_addr = mlx_get_data_addr(texture->img,\
	&texture->bits_per_pixel, &texture->size_line, &texture->endian);
	free(str);
	return (texture);
}

int				get_num(int fd, char *c)
{
	int num;

	num = 0;
	while (*c >= '0' && *c <= '9')
	{
		num = num * 10 + (*c - '0');
		read(fd, c, 1);
	}
	return (num);
}

int				get_color(int fd, char c)
{
	int r;
	int g;
	int b;
	int	t;

	r = -1;
	g = -1;
	b = -1;
	t = 0;
	while (c != '\n')
	{
		if (c >= '0' && c <= '9' && r == -1)
			r = get_num(fd, &c);
		if (c >= '0' && c <= '9' && g == -1)
			g = get_num(fd, &c);
		if (c >= '0' && c <= '9' && b == -1)
			b = get_num(fd, &c);
		if (c != '\n')
			read(fd, &c, 1);
	}
	return ((t << 24 | r << 16 | g << 8 | b));
}

t_textures_data	*get_textures(t_data *data, int fd, char c)
{
	char b;

	read(fd, &b, 1);
	if (c == 'F')
		data->textures->floor = get_color(fd, b);
	else if (c == 'C')
	{
		data->textures->ceiling = get_color(fd, b);
	}
	else if (c == 'S' && b != 'O')
		data->textures->sprite = get_path(b, fd, data);
	else if (c == 'N')
		data->textures->north = get_path(b, fd, data);
	else if (c == 'S')
		data->textures->south = get_path(b, fd, data);
	else if (c == 'E')
		data->textures->east = get_path(b, fd, data);
	else if (c == 'W')
		data->textures->west = get_path(b, fd, data);
	return (data->textures);
}

char			*end_string(int *malloc_size, char *str, int i)
{
	str[i] = 0;
	*malloc_size *= 2;
	str = ft_realloc(str, *malloc_size);
	return (str);
}

t_map_data		*get_map(int fd, t_map_data *map_data, char c)
{
	char	*str;
	int		i;
	int		malloc_size;

	malloc_size = 100;
	i = 1;
	str = ft_calloc(malloc_size, 1);
	str[0] = c;
	while (read(fd, &c, 1))
	{
		if (c != ' ')
		{
			str[i] = c;
			if (c == '2')
				map_data->amouth_of_sprites++;
			i++;
			if (i == (malloc_size - 1))
				str = end_string(&malloc_size, str, i);
		}
	}
	str[i] = '\0';
	map_data->map = str;
	i = 0;
	return (map_data);
}

int				get_dem(int fd, char c)
{
	int num;

	num = 0;
	read(fd, &c, 1);
	while (c == ' ')
		read(fd, &c, 1);
	if (c >= '0' && c <= '9')
	{
		while (c >= '0' && c <= '9')
		{
			num = num * 10 + (c - '0');
			read(fd, &c, 1);
		}
		return (num);
	}
	else
		return (0);
}

t_data			*read_map(t_data *data, char *str)
{
	int		fd;
	char	c;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		exit(print_error(8, 0));
	while (read(fd, &c, 1))
	{
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W' ||\
		c == 'F' || c == 'C')
			data->textures = get_textures(data, fd, c);
		if (c == '1')
		{
			data->map_data = get_map(fd, data->map_data, c);
			close(fd);
			return (data);
		}
		if (c == 'R')
		{
			data->map_data->dem_x = get_dem(fd, c);
			data->map_data->dem_y = get_dem(fd, c);
		}
	}
	close(fd);
	exit(print_error(9, 0));
}
