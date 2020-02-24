/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_main.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 16:00:18 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/23 15:07:49 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	make_img(t_data *data)
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
	(*data).mlx_data.current_img = &(*data).mlx_data.img_1;
}

void	make_window(t_data *data)
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

int		main(int ac, char **av)
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
		return (0);
	read_file(&data, av[1]);
	if (check_map(&data.map_data) == 0)
		return (0);
	data.dda.buffer = malloc(sizeof(double) * data.map_data.dem_x);
	if (data.dda.buffer == NULL)
		return (0);
	map_checking(&data.map_data);
	make_window(&data);
}
