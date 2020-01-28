/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cud3d_keypress.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/18 15:18:47 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/27 20:52:38 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"

int		end_session(t_data *data)
{
	mlx_destroy_window(data->mlx_data->mlx, data->mlx_data->mlx_win);
	exit(0);
}

void	crouch(t_data *data)
{
	data->dda->jump = 0.8;
	make_frame(data);
	data->dda->jump = 1.0;
	//make_frame(data);
}

int		key_press(int keycode, void *param)
{
	if (keycode == 13 || keycode == 126)
		move_forward(param);
	if (keycode == 1 || keycode == 125)
		move_backwards(param);
	if (keycode == 123)
		turn_left(param);
	if (keycode == 124)
		turn_right(param);
	if (keycode == 53 || keycode == 12)
		end_session(param);
	if (keycode == 257)
		crouch(param);
	if (keycode == 2)
		move_left(param);
	if (keycode == 0)
		move_right(param);
	return (1);
}