/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 12:17:20 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/06 13:54:36 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"

static int	check_end_of_line(char *map, t_map_data *data, int i)
{
	int tmp;

	if ((i + 1) % data->x != 0)
		return (0);
	tmp = i - 1;
	if (map[tmp] != '1')
		return (0);
	tmp = i + 1;
	if (map[tmp] != '1' && map[tmp] != 0)
		return (0);
	return (1);
}

t_map_data	*make_map2d(t_map_data *data)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	data->map2d = malloc(sizeof(char *) * (data->y + 1));
	while (data->map[k] != 0)
	{
		data->map2d[j] = malloc(sizeof(char) * data->x);
		while (data->map[k] != '\n' && data->map[k] != '\0')
		{
			data->map2d[j][i] = data->map[k];
			k++;
			i++;
		}
		data->map2d[j][i] = 0;
		i = 0;
		j++;
		k++;
	}
	data->map2d[j] = 0;
	return (data);
}

t_map_data	*get_pos(int i, t_map_data *data, char c)
{
	data->pos_y = i / data->x;
	data->pos_x = i % data->x;
	if (c == 'N' || c == 'S')
		data->dir_x = 0;
	else
		data->dir_y = 0;
	if (c == 'N')
		data->dir_y = -1;
	else if (c == 'S')
		data->dir_y = 1;
	else if (c == 'W')
		data->dir_x = -1;
	else if (c == 'E')
		data->dir_x = 1;
	return (data);
}

int			check_map(t_map_data *data)
{
	int i;

	i = 0;
	while (data->map[i] != '\0')
	{
		if (data->map[i] == 'N' || data->map[i] == 'S' || data->map[i] == 'E' || data->map[i] == 'W')
		{
			if (data->pos_x != 0)
				return (0);
			data = get_pos(i, data, data->map[i]);
		}
		else if (data->map[i] == '\n')
		{
			if (data->x == 0)
				data->x = i + 1;
			if (check_end_of_line(data->map, data, i) == 0)
				return (0);
		}
		else if (data->map[i] < '0' || data->map[i] > '2')
			return (0);
		i++;
	}
	data->y = ((i + 1) / data->x);
	data = make_map2d(data);
	return (1);
}
