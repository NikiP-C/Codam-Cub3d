/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_cud3d.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 16:00:18 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/27 14:54:19 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "cud3d.h"
#include <minilibx_mms_20191025_beta/mlx.h>

t_data	*fill_data(t_data *data)
{
	t_map_data		*map_data;
	t_textures_data	*textures_data;
	t_mlx_data		*mlx_data;
	t_dda			*dda;
	t_wall_size		*wall_size;

	map_data = malloc(sizeof(t_map_data));
	textures_data = malloc(sizeof(t_textures_data));
	mlx_data = malloc(sizeof(t_mlx_data));
	wall_size = malloc(sizeof(t_wall_size));
	dda = malloc(sizeof(t_dda));
	map_data->x = 0;
	map_data->y = 0;
	map_data->pos_x = 0;
	map_data->pos_y = 0;
	data->map_data = map_data;
	data->textures = textures_data;
	data->mlx_data = mlx_data;
	data->dda = dda;
	data->wall_size = wall_size;
	data->map_data->sprite = NULL;
	data->map_data->amouth_of_sprites = 0;
	return (data);
}

int		mouse_press(int button, int x, int y, void *param)
{
	if (x < 0)
		return (0);
	return (0);
}

void	make_window(t_data *data)
{
	data->dda->jump = 1.0;
	data->mlx_data->mlx_win = mlx_new_window(data->mlx_data->mlx,\
		data->map_data->dem_x, data->map_data->dem_y, "Cub3d");
	make_frame(data);
	mlx_hook(data->mlx_data->mlx_win, 2, 1l << 0, key_press, data);
	mlx_hook(data->mlx_data->mlx_win, 4, 1l << 0, mouse_press, data);
	mlx_hook(data->mlx_data->mlx_win, 17, 1l << 17, end_session, data);
	mlx_loop(data->mlx_data->mlx);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	i = 0;
	while (str1[i] == str2[i])
	{
		if (str1[i] == 0 && str2[i] == 0)
			return (0);
		i++;
	}
	return (str1[i] - str2[i]);
}

t_data	*check_save(char *str, t_data *data)
{
	if (!ft_strcmp(str, "--save"))
	{
		printf("AAA\n");
	}
	return (data);
}

int		main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data != 0)
	{
		data = fill_data(data);
		data->mlx_data->mlx = mlx_init();
		if (data->mlx_data->mlx == 0)
			return (0);
	}
	if (data != 0)
		data = read_map(data, av[1]);
	if (ac > 2)
		data = check_save(av[2], data);
	if (data == 0)
		return (0);
	if (check_map(data->map_data) == 0)
		return (0);
	data->dda->buffer = malloc(sizeof(double) * data->map_data->dem_x);
	if (data->dda->buffer == 0)
		return (0);
	data->map_data = make_map2d(data->map_data);
	if (data->map_data == 0)
		return (0);
	make_window(data);
}
