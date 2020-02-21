/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cud3d_read_map.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 13:59:09 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/21 15:30:21 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"

int			make_string_realloc(int fd, char b, char *str, int malloc_size)
{
	int		i;

	i = 0;
	if (str == NULL)
		exit(print_error(16, 0));
	while (b == ' ')
		read(fd, &b, 1);
	while (b != '\n' && b != '\0' && b != ' ')
	{
		str[i] = b;
		i++;
		if (i == malloc_size - 1)
		{
			str[i] = 0;
			malloc_size *= 2;
			ft_realloc(str, malloc_size);
		}
		read(fd, &b, 1);
	}
	str[i] = 0;
	return (i);
}

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
	while (c == ' ')
		read(fd, &c, 1);
	if (c >= '0' && c <= '3')
	{
		(*i)++;
		str[*i] = c;
		if (c == '2' || c == '3')
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

char		*prepare_str(char c, t_map_data *map_data)
{
	char *str;

	str = ft_calloc(100, 1);
	if (str == NULL)
		exit(print_error(16, 0));
	str[0] = c;
	if (c == '2' || c == '3')
		map_data->amouth_of_sprites++;
	return (str);
}

t_map_data	*get_map(int fd, t_map_data *map_data, char c)
{
	char	*str;
	int		i;
	int		malloc_size;

	malloc_size = 100;
	i = 1;
	str = prepare_str(c, map_data);
	while (read(fd, &c, 1) > 0)
	{
		if (c != ' ')
		{
			str[i] = c;
			if (c == '2' || c == '3')
				map_data->amouth_of_sprites++;
			if (c == '\n')
				check_line(str, &i, fd, map_data);
			i++;
			if (i == (malloc_size - 1))
				str = end_string(&malloc_size, str, i);
		}
	}
	str[i] = '\0';
	map_data->map = str;
	return (map_data);
}
