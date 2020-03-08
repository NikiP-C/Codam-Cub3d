/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_read_file_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 11:48:50 by nphilipp       #+#    #+#                */
/*   Updated: 2020/03/08 13:46:04 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void		check_everything(t_error *error)
{
	if ((*error).clg == 0)
		exit(error_missing('C'));
	if ((*error).floor == 0)
		exit(error_missing('F'));
	if ((*error).south == 0)
		exit(error_missing('S'));
	if ((*error).west == 0)
		exit(error_missing('W'));
	if ((*error).east == 0)
		exit(error_missing('E'));
	if ((*error).north == 0)
		exit(error_missing('N'));
	if ((*error).res == 0)
		exit(error_missing('R'));
	if (!(*error).sprite1 || !(*error).sprite2)
		exit(error_missing('P'));
}

static t_data	*map_found(t_error *error, t_data *data, char c, int fd)
{
	check_everything(error);
	get_map(fd, &data->map_data, c);
	close(fd);
	return (data);
}

t_data			*read_file(t_data *data)
{
	char	c;
	int		i;
	t_error	error_check;

	i = 0;
	ft_bzero(&error_check, sizeof(t_error));
	while (read(data->fd, &c, 1))
	{
		if (c == ' ')
			data->map_data.spaces++;
		else if (ft_strchr_no_null("NSEWFCR", c))
			get_textures(data, data->fd, c, &error_check);
		else if (ft_strchr_no_null("0123", c))
			return (map_found(&error_check, data, c, data->fd));
		else if (c == '\n' && data->map_data.spaces != 0)
			exit(print_error(1, 0));
		else if (c != '\n')
			exit(print_error(3, c));
	}
	close(data->fd);
	exit(print_error(9, 0));
	return (data);
}
