/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 12:17:20 by nphilipp       #+#    #+#                */
/*   Updated: 2020/03/04 13:57:43 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_map_data	*get_n_s(t_map_data *data, char c)
{
	data->dir_x = 0;
	if (c == 'N')
		data->dir_y = -1;
	else if (c == 'S')
	{
		data->dir_y = 1;
		data->plane_x = -0.66;
	}
	return (data);
}

t_map_data			*get_pos(int i, int j, t_map_data *data, char c)
{
	data->pos_y = j + 0.5;
	data->pos_x = i + 0.5;
	data->plane_x = 0.66;
	data->plane_y = 0.0;
	if (c == 'N' || c == 'S')
		get_n_s(data, c);
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

char				*ft_strchr_no_null(const char *s, int c)
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

static t_map_data	*check_line_length(int *current_line,\
	t_map_data *data, int i)
{
	if (data->x < *current_line)
		data->x = *current_line;
	*current_line = 0;
	if (data->map[i + 1] != '\n')
		data->y++;
	return (data);
}

int					check_map(t_map_data *data)
{
	int i;
	int current_line;

	i = 0;
	current_line = 0;
	while (data->map[i] != '\0')
	{
		if (ft_strchr_no_null("NESW", data->map[i]))
		{
			if (data->pos_x != 0)
				exit(print_error(2, 0));
			data->pos_x = 1;
		}
		else if (data->map[i] == '\n')
			check_line_length(&current_line, data, i);
		else if ((data->map[i] < '0' || data->map[i] > '2') \
		&& data->map[i] != ' ')
			exit(print_error(3, data->map[i]));
		i++;
		current_line++;
	}
	if (data->pos_x == 0)
		exit(print_error(4, 0));
	return (1);
}
