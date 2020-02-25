/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_keypress_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/18 15:18:47 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/25 15:56:33 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int		end_session(t_data *data)
{
	mlx_destroy_image((*data).mlx_data.mlx, (*data).mlx_data.img_1.mlx_img);
	mlx_destroy_image((*data).mlx_data.mlx, (*data).mlx_data.img_2.mlx_img);
	mlx_destroy_image((*data).mlx_data.mlx, (*data).textures.sprite_1.img);
	mlx_destroy_image((*data).mlx_data.mlx, (*data).textures.sprite_2.img);
	mlx_destroy_image((*data).mlx_data.mlx, (*data).textures.south.img);
	mlx_destroy_image((*data).mlx_data.mlx, (*data).textures.north.img);
	mlx_destroy_image((*data).mlx_data.mlx, (*data).textures.west.img);
	mlx_destroy_image((*data).mlx_data.mlx, (*data).textures.east.img);
	mlx_destroy_window((*data).mlx_data.mlx, (*data).mlx_data.mlx_win);
	exit(1);
	return (0);
}

int		key_press(int keycode, void *param)
{
	t_data *data;

	data = param;
	if (keycode == 13 || keycode == 126)
		(*data).keys.walk_forward = 1;
	if (keycode == 1 || keycode == 125)
		(*data).keys.walk_backwards = 1;
	if (keycode == 123)
		(*data).keys.look_left = 1;
	if (keycode == 124)
		(*data).keys.look_right = 1;
	if (keycode == 53 || keycode == 12)
		end_session(param);
	if (keycode == 2)
		(*data).keys.walk_left = 1;
	if (keycode == 0)
		(*data).keys.walk_right = 1;
	return (1);
}

int		key_release(int keycode, void *param)
{
	t_data *data;

	data = param;
	if (keycode == 13 || keycode == 126)
		(*data).keys.walk_forward = 0;
	if (keycode == 1 || keycode == 125)
		(*data).keys.walk_backwards = 0;
	if (keycode == 123)
		(*data).keys.look_left = 0;
	if (keycode == 124)
		(*data).keys.look_right = 0;
	if (keycode == 2)
		(*data).keys.walk_left = 0;
	if (keycode == 0)
		(*data).keys.walk_right = 0;
	return (1);
}

void	turn_left(t_data *data)
{
	double old_dirx;
	double old_planex;

	old_dirx = (*data).map_data.dir_x;
	old_planex = (*data).map_data.plane_x;
	(*data).map_data.dir_x = (*data).map_data.dir_x \
	* cos(0.02) - (*data).map_data.dir_y * sin(-0.02);
	(*data).map_data.dir_y = old_dirx * sin(-0.02) + \
	(*data).map_data.dir_y * cos(-0.02);
	(*data).map_data.plane_x = old_planex * cos(-0.02) - \
	(*data).map_data.plane_y * sin(-0.02);
	(*data).map_data.plane_y = old_planex * sin(-0.02) + \
	(*data).map_data.plane_y * cos(-0.02);
}

void	turn_right(t_data *data)
{
	double old_dirx;
	double old_planex;

	old_dirx = (*data).map_data.dir_x;
	old_planex = (*data).map_data.plane_x;
	(*data).map_data.dir_x = (*data).map_data.dir_x * \
	cos(-0.02) - (*data).map_data.dir_y * sin(0.02);
	(*data).map_data.dir_y = old_dirx * sin(0.02) + \
	(*data).map_data.dir_y * cos(0.02);
	(*data).map_data.plane_x = old_planex * cos(0.02) - \
	(*data).map_data.plane_y * sin(0.02);
	(*data).map_data.plane_y = old_planex * sin(0.02) + \
	(*data).map_data.plane_y * cos(0.02);
}
