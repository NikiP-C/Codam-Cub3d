/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_read_map.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 13:59:09 by nphilipp       #+#    #+#                */
/*   Updated: 2020/03/03 21:18:12 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*end_string(int *malloc_size, char *str, int i)
{
	str[i] = 0;
	*malloc_size *= 2;
	str = ft_realloc(str, *malloc_size);
	return (str);
}

static int	check_line(char *str, int *i, int fd, t_map_data *data)
{
	char c;

	read(fd, &c, 1);
	if ((c >= '0' && c <= '2') || c == ' ')
	{
		(*i)++;
		str[*i] = c;
		if (c == '2')
			data->amouth_of_sprites++;
		return (0);
	}
	while (c == '\n')
	{
		if (!read(fd, &c, 1))
			return (1);
	}
	exit(print_error(6, 0));
}

char		*prepare_str(char c, t_map_data *map_data, int *i)
{
	char *str;

	str = ft_calloc(100, 1);
	if (str == NULL)
		exit(print_error(16, 0));
	while (map_data->spaces)
	{
		str[*i] = ' ';
		map_data->spaces--;
		(*i)++;
	}
	str[*i] = c;
	(*i)++;
	if (c == '2')
		map_data->amouth_of_sprites++;
	return (str);
}

t_map_data	*get_map(int fd, t_map_data *map_data, char c)
{
	char	*str;
	int		i;
	int		malloc_size;

	malloc_size = 100;
	i = 0;
	str = prepare_str(c, map_data, &i);
	while (read(fd, &c, 1) > 0)
	{
		str[i] = c;
		if (c == '2')
			map_data->amouth_of_sprites++;
		if (c == '\n')
			check_line(str, &i, fd, map_data);
		i++;
		if (i == (malloc_size - 1))
			str = end_string(&malloc_size, str, i);
	}
	str[i] = '\0';
	map_data->map = str;
	return (map_data);
}
