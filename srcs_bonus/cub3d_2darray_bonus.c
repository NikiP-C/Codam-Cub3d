/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_2darray_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 11:30:26 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/25 17:31:16 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

char	*make_string(char *map, int x, int *k)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_calloc(x + 1, sizeof(char));
	if (str == NULL)
		exit(print_error(16, 0));
	while (map[*k] != '\n' && map[*k] != '\0')
	{
		str[i] = map[*k];
		i++;
		(*k)++;
	}
	str[i] = '\0';
	return (str);
}

char	**make_2darray(char *str, int y, int x)
{
	int		j;
	int		k;
	char	**array;

	j = 0;
	k = 0;
	array = ft_calloc(y + 2, sizeof(char *));
	if (array == NULL)
		exit(print_error(16, 0));
	while (str[k] != 0)
	{
		if (str[k] != '\n' && str[k] != 0)
		{
			array[j] = make_string(str, x, &k);
			j++;
		}
		else if (str[k] == '\n')
			k++;
	}
	array[j] = NULL;
	return (array);
}

void	get_start_pos(t_map_data *data)
{
	int i;
	int j;

	j = 0;
	while (data->map2d[j] != NULL)
	{
		i = 0;
		while (data->map2d[j][i] != '\0')
		{
			if (ft_strchr_no_null("NSWE", data->map2d[j][i]))
			{
				get_pos(i, j, data, data->map2d[j][i]);
				data->map2d[j][i] = '0';
				return ;
			}
			i++;
		}
		j++;
	}
}

void	map_checking(t_map_data *data)
{
	char **back_up_map;

	back_up_map = NULL;
	data->map2d = make_2darray(data->map, data->y, data->x);
	find_sprites(data);
	get_start_pos(data);
	back_up_map = make_2darray(data->map, data->y, data->x);
	free(data->map);
	back_up_map[(int)data->pos_y][(int)data->pos_x] = '0';
	if (!flood_fill(back_up_map, data->pos_x, data->pos_y))
	{
		free_2darray(back_up_map);
		free_2darray(data->map2d);
		exit(print_error(7, 0));
	}
	free_2darray(back_up_map);
}
