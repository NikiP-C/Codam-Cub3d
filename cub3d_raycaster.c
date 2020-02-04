/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_raycaster.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 12:09:17 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/04 11:16:05 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"
#include <math.h>

t_dda		*decide_step(t_dda *dda, t_map_data *data)
{
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->sidedis_x = (data->pos_x - dda->map_x) * dda->deltadis_x;
	}
	else
	{
		dda->step_x = 1;
		dda->sidedis_x = (dda->map_x + 1.0 - data->pos_x) * dda->deltadis_x;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->sidedis_y = (data->pos_y - dda->map_y) * dda->deltadis_y;
	}
	else
	{
		dda->step_y = 1;
		dda->sidedis_y = (dda->map_y + 1.0 - data->pos_y) * dda->deltadis_y;
	}
	return (dda);
}

t_dda		*find_collison(t_dda *dda, t_data *data)
{
	dda->hit = 0;
	while (dda->hit == 0)
	{
		if (dda->sidedis_x < dda->sidedis_y)
		{
			dda->sidedis_x += dda->deltadis_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->sidedis_y += dda->deltadis_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (data->map_data->map2d[dda->map_y][dda->map_x] == '1')
			dda->hit = 1;
	}
	if (dda->side == 0)
		dda->perpwall_dist = (dda->map_x\
			- data->map_data->pos_x + (1 - dda->step_x) / 2) / dda->ray_dir_x;
	else
		dda->perpwall_dist = (dda->map_y\
		- data->map_data->pos_y + (1 - dda->step_y) / 2) / dda->ray_dir_y;
	return (dda);
}

t_wall_size	*calculate_wall(t_data *data, t_wall_size *wall_size)
{
	wall_size->lineheight = \
	(int)(data->map_data->dem_y / data->dda->perpwall_dist);
	wall_size->drawstart = data->dda->jump *\
	((-wall_size->lineheight / 2) + (data->map_data->dem_y / 2));
	if (wall_size->drawstart < 0)
		wall_size->drawstart = 0;
	wall_size->drawend = data->dda->jump * ((wall_size->lineheight / 2) +\
	(data->map_data->dem_y / 2));
	if (wall_size->drawend >= data->map_data->dem_y)
		wall_size->drawend = (data->map_data->dem_y - 1);
	return (wall_size);
}

t_data		*raycasting(t_data *data)
{
	int		x;
	double	camera_x;

	x = 0;
	while (x < data->map_data->dem_x)
	{
		camera_x = 2 * x / (double)data->map_data->dem_x - 1;
		data->dda->ray_dir_x = data->map_data->dir_x\
		+ data->map_data->plane_x * camera_x;
		data->dda->ray_dir_y = data->map_data->dir_y\
		+ data->map_data->plane_y * camera_x;
		data->dda->map_x = data->map_data->pos_x;
		data->dda->map_y = data->map_data->pos_y;
		data->dda->deltadis_x = fabs(1 / data->dda->ray_dir_x);
		data->dda->deltadis_y = fabs(1 / data->dda->ray_dir_y);
		data->dda = decide_step(data->dda, data->map_data);
		data->dda = find_collison(data->dda, data);
		data->wall_size = calculate_wall(data, data->wall_size);
		data = choose_side(data, x);
		data->dda->buffer[x] = data->dda->perpwall_dist;
		x++;
	}
	data = sprites(data);
	put_healthbar(data);
	return (data);
}

void		make_frame(t_data *data)
{
	if (data->dda->life <= 0)
	{
		//death_screen
		;
	}
	data->mlx_data->mlx_img = \
		mlx_new_image(data->mlx_data->mlx, data->map_data->dem_x,
		data->map_data->dem_x);
	data->mlx_data->mlx_addr = \
		mlx_get_data_addr(data->mlx_data->mlx_img, \
			&data->mlx_data->bits_per_pixel, \
				&data->mlx_data->line_lenght, &data->mlx_data->endian);
	data = raycasting(data);
	if (data->safe == 1)
	{
		make_bitmap(data);
		data->safe = 0;
	}
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->mlx_win, \
		data->mlx_data->mlx_img, 0, 0);
}
