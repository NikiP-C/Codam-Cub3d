/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 14:00:39 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/22 16:39:36 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../cub3d.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	int pos;

	if (x >= 0 && x < (*data).map_data.dem_x && y >= 0\
	&& y < (*data).map_data.dem_y)
	{
		pos = (y * (*data).mlx_data.current_img->line_lenght) + x *\
		((*data).mlx_data.current_img->bits_per_pixel / 8);
		*(unsigned int *)((*data).mlx_data.current_img->mlx_addr + pos) = color;
	}
}

char	*ft_realloc(char *str, int malloc_size)
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = ft_calloc(malloc_size, 1);
	if (newstr == NULL)
		exit(print_error(16, 0));
	while (str[i])
	{
		newstr[i] = str[i];
		i++;
	}
	free(str);
	return (newstr);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	i = 0;
	while (str1[i] == str2[i])
	{
		if (str1[i] == 0 && str2[i] == 0)
			return (0);
		i++;
	}
	return (str1[i] - str2[i]);
}

void	free_2darray(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int		flood_fill(char **map, int x, int y)
{
	if (map[y] == NULL)
		return (0);
	if (y > 0 && x > 0 && ft_strchr_no_null("023", map[y][x]))
	{
		map[y][x] = 'x';
		if (!flood_fill(map, x, y + 1))
			return (0);
		if (!flood_fill(map, x + 1, y))
			return (0);
		if (!flood_fill(map, x, y - 1))
			return (0);
		if (!flood_fill(map, x - 1, y))
			return (0);
		if (!flood_fill(map, x + 1, y + 1))
			return (0);
		if (!flood_fill(map, x + 1, y - 1))
			return (0);
		if (!flood_fill(map, x - 1, y - 1))
			return (0);
		if (!flood_fill(map, x - 1, y + 1))
			return (0);
	}
	if (map[y][x] == '1' || map[y][x] == 'x')
		return (1);
	return (0);
}
