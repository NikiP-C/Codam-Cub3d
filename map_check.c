/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 12:17:20 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/27 15:35:31 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"

t_map_data	*get_pos(int i, int j, t_map_data *data, char c)
{
	data->pos_y = j + 0.5;
	data->pos_x = i + 0.5;
	data->plane_x = 0.66;
	data->plane_y = 0.0;
	if (c == 'N' || c == 'S')
		data->dir_x = 0;
	else
		data->dir_y = 0;
	if (c == 'N')
		data->dir_y = -1;
	else if (c == 'S')
		data->dir_y = 1;
	else if (c == 'W')
	{
		data->dir_x = -1;
		data->plane_x = 0.0;
		data->plane_y = -0.66;
	}
	else if (c == 'E')
	{
		data->dir_x = 1;
		data->plane_x = 0.0;
		data->plane_y = 0.66;
	}
	return (data);
}

char	*ft_strchr_no_null(const char *s, int c)
{
	int		i;
	char	*str2;

	i = 0;
	str2 = (char*)s;
	while (str2[i] != 0)
	{
		if (str2[i] == c)
		{
			return (str2 + i);
		}
		i++;
	}
	return (0);
}

int		check_map(t_map_data *data)
{
	int i;
	int longestline;

	i = 0;
	longestline = 0;
	while (data->map[i] != '\0')
	{
		if (ft_strchr_no_null("NESW", data->map[i]))
		{
			if (data->pos_x != 0)
				exit(print_error(2, 0));
			data->pos_x = 1;
		}
		else if (data->map[i] == '\n')
		{
			if (data->x < longestline)
				data->x = longestline;
			longestline = 0;
		}
		else if (data->map[i] < '0' || data->map[i] > '2')
			return (print_error(3, data->map[i]));
		i++;
		longestline++;
	}
	if (data->pos_x == 0)
		exit(print_error(4, 0));
	data->y = ((i + 1) / data->x);
	return (1);
}
