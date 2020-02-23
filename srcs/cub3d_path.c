/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 23:07:51 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/22 16:39:36 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*remove_spaces(int i, char *str)
{
	while (str[i] == ' ')
	{
		str[i] = 0;
		i--;
	}
	if (ft_strcmp(&str[i - 3], ".png"))
		exit(print_error(11, 0));
	return (str);
}

static char	*make_string_realloc(int fd, char b, char *str, int malloc_size)
{
	int		i;

	i = 0;
	if (str == NULL)
		exit(print_error(16, 0));
	while (b == ' ')
		read(fd, &b, 1);
	while (b != '\n' && b != '\0')
	{
		str[i] = b;
		i++;
		if (i == malloc_size - 1)
		{
			str[i] = 0;
			malloc_size *= 2;
			str = ft_realloc(str, malloc_size);
		}
		read(fd, &b, 1);
	}
	str[i] = 0;
	return (remove_spaces(i - 1, str));
}

t_texture	get_path(char b, int fd, t_data *data, int *error)
{
	char		*str;
	t_texture	tex;

	ft_bzero(&tex, sizeof(t_texture));
	*error = 1;
	str = ft_calloc(sizeof(char), 20);
	if (str == NULL)
		exit(print_error(16, 0));
	str = make_string_realloc(fd, b, str, 20);
	tex.img = mlx_png_file_to_image((*data).mlx_data.mlx,\
					str, &tex.width, &tex.height);
	if (tex.img == NULL)
		exit(print_error(12, 0));
	tex.img_addr = mlx_get_data_addr(tex.img, &tex.bits_per_pixel, \
			&tex.size_line, &tex.endian);
	free(str);
	return (tex);
}
