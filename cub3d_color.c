/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_color.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 12:46:35 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/03 15:04:21 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"
#include <minilibx_mms_20191025_beta/mlx.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>

void	put_healthbar(t_data *data)
{
	int end[2];
	int y;
	int x;

	end[0] = data->map_data->dem_y / 50 * 48;
	end[1] = data->map_data->dem_x / 6 * 5;
	y = data->map_data->dem_y / 50 * 47;
	while (y < end[0])
	{
		x = data->map_data->dem_x / 6;
		while (x != end[1])
		{
			if (x < (int)((double)end[1] * data->dda->life))
				put_pixel(data, x, y, 0x0000FF00);
			else
				put_pixel(data, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
}

void	put_floor_ceiling(t_data *data, int x)
{
	int y;

	y = 0;
	while (y < data->wall_size->drawstart)
	{
		put_pixel(data, x, y, data->textures->ceiling);
		y++;
	}
	y = data->wall_size->drawend + 1;
	while (y < data->map_data->dem_y)
	{
		put_pixel(data, x, y, data->textures->floor);
		y++;
	}
}

void	put_line(t_data *data, int x, t_texture *tex, t_vsi *tx_pix)
{
	int				y;
	char			*test;
	unsigned int	color;
	double			step;
	double			texpos;

	y = data->wall_size->drawstart;
	step = (1.0 * tex->height) / data->wall_size->lineheight;
	texpos = (data->wall_size->drawstart - (data->map_data->dem_y / 2.0)\
	+ (data->wall_size->lineheight / 2.0)) * step;
	put_floor_ceiling(data, x);
	while (y <= data->wall_size->drawend)
	{
		tx_pix->y = (int)texpos & (tex->height - 1);
		texpos += step;
		test = tex->img_addr + (tex->size_line * (int)texpos \
		+ tx_pix->x * (tex->bits_per_pixel / 8));
		color = *((int *)test);
		put_pixel(data, x, y, color);
		y++;
	}
}

t_data	*pick_texture(t_data *data, int x, t_texture *tex)
{
	double			wallx;
	t_vsi			*tx_pix;

	tx_pix = malloc(sizeof(t_vsi));
	if (data->dda->side == 0)
	{
		wallx = (double)data->map_data->pos_y + \
		(data->dda->perpwall_dist * data->dda->ray_dir_y);
	}
	else
	{
		wallx = (double)data->map_data->pos_x + \
			(data->dda->perpwall_dist * data->dda->ray_dir_x);
	}
	wallx -= floor((wallx));
	tx_pix->x = (int)(wallx * (double)tex->width);
	if (data->dda->side == 0 && data->dda->ray_dir_x > 0)
		tx_pix->x = tex->width - tx_pix->x - 1;
	if (data->dda->side == 1 && data->dda->ray_dir_y < 0)
		tx_pix->x = tex->width - tx_pix->x - 1;
	put_line(data, x, tex, tx_pix);
	free(tx_pix);
	return (data);
}

t_data	*choose_side(t_data *data, int x)
{
	if (data->dda->side)
	{
		if (data->dda->ray_dir_y >= 0)
			data = pick_texture(data, x, data->textures->north);
		else
			data = pick_texture(data, x, data->textures->south);
	}
	else
	{
		if (data->dda->ray_dir_x >= 0)
			data = pick_texture(data, x, data->textures->east);
		else
			data = pick_texture(data, x, data->textures->west);
	}
	return (data);
}
