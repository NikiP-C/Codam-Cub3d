/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_read_file.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 11:48:50 by nphilipp       #+#    #+#                */
/*   Updated: 2020/03/08 13:11:57 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	if ((*error).sprite1 == 0)
		exit(error_missing('P'));
	if (error->res == 0)
		exit(error_missing('R'));
}

static int		open_file(char *str)
{
	int fd;
	int i;

	i = 0;
	while (str[i])
		i++;
	if (ft_strcmp(".cub", &str[i - 4]))
	{
		write(2, "ERROR\nWrong file type.\n", 23);
		exit(0);
	}
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		write(2, "ERROR\nWrong file type.\n", 23);
		exit(0);
	}
	return (fd);
}

static t_data	*map_found(t_error *error, t_data *data, char c, int fd)
{
	check_everything(error);
	get_map(fd, &data->map_data, c);
	close(fd);
	return (data);
}

t_data			*read_file(t_data *data, char *str)
{
	int		fd;
	char	c;
	int		i;
	t_error	error_check;

	i = 0;
	fd = open_file(str);
	ft_bzero(&error_check, sizeof(t_error));
	if (fd < 0)
		exit(print_error(8, 0));
	while (read(fd, &c, 1))
	{
		if (c == ' ')
			data->map_data.spaces++;
		else if (ft_strchr_no_null("NSEWFCR", c))
			get_textures(data, fd, c, &error_check);
		else if (ft_strchr_no_null("012", c))
			return (map_found(&error_check, data, c, fd));
		else if (c == '\n' && data->map_data.spaces != 0)
			exit(error_message("Spaces found on empty line\n"));
		else if (c != '\n')
			exit(print_error(3, c));
	}
	exit(print_error(9, fd));
	return (data);
}
