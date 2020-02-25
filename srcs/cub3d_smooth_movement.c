/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_smooth_movement.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/02 17:49:11 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/25 15:50:09 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_states(t_keys keys)
{
	if (keys.walk_forward || keys.walk_backwards || keys.walk_left || \
		keys.walk_right || keys.look_right || keys.look_left)
		return (1);
	return (0);
}

static void	switch_image(t_data *data, int count)
{
	if (count % 2)
		(*data).mlx_data.current_img = &(*data).mlx_data.img_2;
	else
		(*data).mlx_data.current_img = &(*data).mlx_data.img_1;
}

int			movement(void *param)
{
	static int	count = 1;

	if (check_states(((t_data *)(param))->keys))
	{
		if (((t_data *)(param))->keys.walk_backwards)
			move_backwards(param);
		if (((t_data *)(param))->keys.walk_forward)
			move_forward(param);
		if (((t_data *)(param))->keys.walk_left)
			move_left(param);
		if (((t_data *)(param))->keys.walk_right)
			move_right(param);
		if (((t_data *)(param))->keys.look_left)
			turn_left(param);
		if (((t_data *)(param))->keys.look_right)
			turn_right(param);
		switch_image(param, count);
		count++;
		make_frame(param);
	}
	return (1);
}
