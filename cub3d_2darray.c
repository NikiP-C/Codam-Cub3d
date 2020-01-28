/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_2darray.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 17:30:21 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/27 20:52:06 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"

t_map_data	*make_map2d(t_map_data *data)
{
	int j;
	int k;
	int i;
	
	j = 0;
	k = 0;
	data->map2d = ft_calloc(data->y + 1, sizeof(char *));
	data->map2d[j] = ft_calloc(data->x + 1, sizeof(char));
	while (data->map[k] != 0)
	{
		i = 0;
		while (data->map[k] != '\n' && data->map[k] != 0)
		{
			data->map2d[j][i] = data->map[k];
			k++;
			i++;
			if (data->map[k] == '2')
				data = sprite_data(data, j, i);
			if (ft_strchr_no_null("NESW", data->map[k]))
			{
				data = get_pos(i, j, data, data->map[k]);
				data->map[k] = '0';
			}
		}
		if (i != 0)
		{
			data->map2d[j][i] = 0;
			j++;
			data->map2d[j] = ft_calloc(data->x + 1, sizeof(char));
		}
		k++;
	}
	data->map2d[j] = NULL;
	check_top_bottom(data);
	is_map_closed(data);
	free(data->map);
	return (data);
}

void	check_line(int j, int i, t_map_data *data)
{
	int k;

	k = 0;
	if (j < 0 || data->map2d[j] == NULL)
		return ;
	while (data->map2d[j][k])
		k++;
	if (k > (i + 1))
	{
		if (data->map2d[j][i] != '1')
			exit(print_error(7, 0));
	}
}

void	is_map_closed(t_map_data *data)
{
	int i;
	int j;

	j = 0;
	while (data->map2d[j] != NULL)
	{
		i = 0;
		while (data->map2d[j][i])
			i++;
		check_line(j - 1, i - 1, data);
		check_line(j + 1, i - 1, data);
		j++;
	}
}

int	check_top_bottom(t_map_data *data)
{
	int i;

	i = 0;
	twod_array_printer(data->map2d);
	while (data->map2d[0][i])
	{
		if (data->map2d[0][i] != '1')
			exit(print_error(6, 0));
		i++;
	}
	i = 0;
	while (data->map2d[data->y - 1][i])
	{
		if (data->map2d[data->y - 1][i] != '1')
			exit(print_error(5, 0));
		i++;
	}
	return (1);
}
