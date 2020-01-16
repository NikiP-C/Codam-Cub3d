/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_cud3d.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/30 16:00:18 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/16 19:49:44 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "cud3d.h"
#include <minilibx_mms_20191025_beta/mlx.h>
#include <math.h>

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
	return (data);
}

int move_forward(t_data *data)
{
	if (data->map_data->map2d[(int)(data->map_data->pos_y)]\
		[(int)(data->map_data->pos_x + data->map_data->dir_x * 0.2)] != '1')
	{
		data->map_data->pos_x += data->map_data->dir_x * 0.2;
	}
	if (data->map_data->map2d[(int)(data->map_data->pos_y + data->map_data->dir_y * 0.2)]\
		[(int)data->map_data->pos_x] != '1')
	{
		data->map_data->pos_y += data->map_data->dir_y * 0.2;
	}
	make_frame(data);
	return (0);
} 

int move_backwards(t_data *data)
{
	if (data->map_data->map2d[(int)(data->map_data->pos_y)]\
		[(int)(data->map_data->pos_x - data->map_data->dir_x * 0.2)] != '1')
	{
		data->map_data->pos_x -= data->map_data->dir_x * 0.2;
	}
	if (data->map_data->map2d[(int)(data->map_data->pos_y - data->map_data->dir_y * 0.2)]\
		[(int)data->map_data->pos_x] != '1')
	{
		data->map_data->pos_y -= data->map_data->dir_y * 0.2;
	}
	make_frame(data);
	return (0);
}

int turn_left(t_data *data)
{
	double old_dirx;
	double old_planex;

	old_dirx = data->map_data->dir_x;
	old_planex = data->map_data->plane_x;
	data->map_data->dir_x = data->map_data->dir_x * cos(0.1) - data->map_data->dir_y * sin(0.1);
	data->map_data->dir_y = old_dirx * sin(0.1) + data->map_data->dir_y * cos(0.1);
	data->map_data->plane_x = old_planex * cos(0.1) - data->map_data->plane_y * sin(0.1);
	data->map_data->plane_y = old_planex * sin(0.1) + data->map_data->plane_y * cos(0.1);
	make_frame(data);
	return (0);
}

int turn_right(t_data *data)
{
	double old_dirx;
	double old_planex;

	old_dirx = data->map_data->dir_x;
	old_planex = data->map_data->plane_x;
	data->map_data->dir_x = data->map_data->dir_x * cos(-0.1) - data->map_data->dir_y * sin(-0.1);
	data->map_data->dir_y = old_dirx * sin(-0.1) + data->map_data->dir_y * cos(-0.1);
	data->map_data->plane_x = old_planex * cos(-0.1) - data->map_data->plane_y * sin(-0.1);
	data->map_data->plane_y = old_planex * sin(-0.1) + data->map_data->plane_y * cos(-0.1);
	make_frame(data);
	return (0);
}

void	end_session(t_data *data)
{
	mlx_destroy_window(data->mlx_data->mlx, data->mlx_data->mlx_win);
}

int		key_press(int keycode, void *param)
{
	if (keycode == 13 || keycode == 126)
		move_forward(param);
	if (keycode == 1 || keycode == 125)
		move_backwards(param);
	if (keycode == 0 || keycode == 123)
		turn_left(param);
	if (keycode == 2 || keycode == 124)
		turn_right(param);
	if (keycode == 53 || keycode == 12)
		end_session(param);
	return (1);
}

void	make_window(t_data *data)
{
	int color;
	data->mlx_data->mlx_win = mlx_new_window(data->mlx_data->mlx,\
		data->map_data->dem_x, data->map_data->dem_y, "Cud3d");
	make_frame(data);
	mlx_hook(data->mlx_data->mlx_win, 2, 1l << 0, key_press, data);
	mlx_loop(data->mlx_data->mlx);
}

int				main(void)
{
	t_data	*data;
	int		error;

	data = malloc(sizeof(t_data));
	if (data != 0)
	{
		data = fill_data(data);
		data->mlx_data->mlx = mlx_init();
		if (data->mlx_data->mlx == 0)
			return (0);
	}
	if (data != 0)
		data = read_map(data);
	if (data == 0)
		return (0);
	error = check_map(data->map_data);
	data->map_data->plane_x = -1.0;
	data->map_data->plane_y = 0.66;
	make_window(data);
}
