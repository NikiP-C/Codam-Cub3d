/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_main_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 16:00:18 by nphilipp       #+#    #+#                */
/*   Updated: 2020/03/08 13:42:30 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void		make_img(t_data *data)
{
	(*data).mlx_data.img_1.mlx_img = mlx_new_image((*data).mlx_data.mlx,\
		(*data).map_data.dem_x, (*data).map_data.dem_y);
	(*data).mlx_data.img_2.mlx_img = mlx_new_image((*data).mlx_data.mlx,\
		(*data).map_data.dem_x, (*data).map_data.dem_y);
	if (!(*data).mlx_data.img_1.mlx_img || !(*data).mlx_data.img_1.mlx_img)
		exit(print_error(15, 0));
	(*data).mlx_data.img_1.mlx_addr = mlx_get_data_addr((*data).\
		mlx_data.img_1.mlx_img, &(*data).mlx_data.img_1.bits_per_pixel,
		&(*data).mlx_data.img_1.line_lenght, &(*data).mlx_data.img_1.endian);
	(*data).mlx_data.img_2.mlx_addr = mlx_get_data_addr((*data).\
		mlx_data.img_2.mlx_img, &(*data).mlx_data.img_2.bits_per_pixel,
		&(*data).mlx_data.img_2.line_lenght, &(*data).mlx_data.img_2.endian);
	if (!(*data).mlx_data.img_1.mlx_addr || !(*data).mlx_data.img_1.mlx_addr)
		exit(print_error(15, 0));
	(*data).mlx_data.current_img = &(*data).mlx_data.img_1;
}

static int	open_file(char *str)
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

void		make_window(t_data *data)
{
	if (!(*data).safe)
	{
		(*data).mlx_data.mlx_win = mlx_new_window((*data).mlx_data.mlx,\
			(*data).map_data.dem_x, (*data).map_data.dem_y, "Cub3d");
		if ((*data).mlx_data.mlx_win == NULL)
			exit(print_error(14, 0));
	}
	make_img(data);
	make_frame(data);
	mlx_hook((*data).mlx_data.mlx_win, 2, 1l << 0, key_press, data);
	mlx_hook((*data).mlx_data.mlx_win, 3, 1l << 1, key_release, data);
	mlx_hook((*data).mlx_data.mlx_win, 17, 1l << 17, end_session, data);
	mlx_loop_hook((*data).mlx_data.mlx, movement, data);
	mlx_loop((*data).mlx_data.mlx);
}

static void	init_data(t_data *data, char *str)
{
	data->textures.floor = -1;
	data->textures.clg = -1;
	data->fd = open_file(str);
	if (data->fd < 0)
		exit(print_error(8, 0));
	read_file(data);
}

int			main(int ac, char **av)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (ac == 3)
	{
		if (!ft_strcmp(av[2], "--save"))
			data.safe = 1;
		else
			exit(print_error(17, 0));
	}
	else if (ac != 2)
		exit(print_error(18, 0));
	data.mlx_data.mlx = mlx_init();
	if (data.mlx_data.mlx == 0)
		return (print_error(16, 0));
	init_data(&data, av[1]);
	data.dda.life = 1;
	check_map(&data.map_data);
	data.dda.buffer = malloc(sizeof(double) * data.map_data.dem_x);
	if (data.dda.buffer == NULL)
		return (print_error(16, 0));
	map_checking(&data.map_data);
	make_window(&data);
	return (0);
}
