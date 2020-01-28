/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_color.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/13 12:46:35 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/22 12:29:20 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"
#include <minilibx_mms_20191025_beta/mlx.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>

t_data	*pick_color(t_data *data, int x)
{
	int h;
	int color;

	h = 0;
	if (data->dda->side == 1)
		color = 0x00FF0000;
	else
		color = 0x00fa6f5a;
	while (h < data->map_data->dem_y)
	{
		if (h < data->wall_size->drawstart)
			put_pixel(data, x, h, data->textures->ceiling); 
		else if (h > data->wall_size->drawend)
			put_pixel(data, x, h, data->textures->floor); 
		else
			put_pixel(data, x, h, color);
		h++;
	}
	return (data);
}

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
			if (x < data->map_data->dem_x / 6 * 4)
				put_pixel(data, x, y, 0x0000FF00);
			else
				put_pixel(data, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
}

t_data	*pick_texture(t_data *data, int x, t_texture *tex)
{
	int				y;
	int				tex_y;
	unsigned int	color;
	char			*test;
	double 			step;
	double			texpos;
	double			wallx;
	int				tex_x;

	if (data->dda->side == 0)
	{
		wallx = (double)data->map_data->pos_y + (data->dda->perpwall_dist * data->dda->ray_dir_y);
	}
	else
	{
		wallx = (double)data->map_data->pos_x + (data->dda->perpwall_dist * data->dda->ray_dir_x);
	}
	wallx -= floor((wallx));
	tex_x = (int)(wallx * (double)tex->width);
	if (data->dda->side == 0 && data->dda->ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (data->dda->side == 1 && data->dda->ray_dir_x < 0)
		tex_x = tex->width - tex_x - 1;
	step = (1.0 * tex->height) / data->wall_size->lineheight;
	texpos = (data->wall_size->drawstart - (data->map_data->dem_y / 2.0) + (data->wall_size->lineheight / 2.0)) * step;
	y = 0;
	while (y < data->map_data->dem_y)
	{
		if (y < data->wall_size->drawstart)
			put_pixel(data, x, y, data->textures->ceiling);
		else if (y < data->wall_size->drawend)
		{
			tex_y = (int)texpos & (tex->height - 1);
			texpos += step;
			test = tex->img_addr + tex->size_line * tex_y + tex_x * (tex->bits_per_pixel / 8);
			color = *((int *)test);
			put_pixel(data, x, y, color);
		}
		else
			put_pixel(data, x, y, data->textures->floor);
		y++;
	}
	return (data);
}

t_data *choose_side(t_data *data, int x)
{
	if (data->dda->side)
	{
		if (data->dda->ray_dir_y > 0)
			data = pick_texture(data, x, data->textures->north);
		else
			data = pick_texture(data, x, data->textures->south);
		
	}
	else
	{
		if (data->dda->ray_dir_x > 0)
			data = pick_texture(data, x, data->textures->east);
		else
			data = pick_texture(data, x, data->textures->west);
	}
	return(data);
}
