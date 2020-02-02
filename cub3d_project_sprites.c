/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_project_sprites.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 23:17:09 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/01 12:33:40 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"

void	sprite_pixel(t_data *data, t_sprite_data *s_data, int stripe, int y)
{
	unsigned int	color;
	char			*test;

	s_data->d = (y) * 256 - data->map_data->dem_y * \
		128 + s_data->sprite_height * 128;
	s_data->tex_y = ((s_data->d * data->textures->sprite->height) \
		/ s_data->sprite_height) / 256;
	test = data->textures->sprite->img_addr + \
	(data->textures->sprite->size_line * s_data->tex_y) \
		+ s_data->tex_x * (data->textures->sprite->bits_per_pixel / 8);
	color = *((unsigned int *)test);
	if ((color & 0x00FFFFFF) != 0)
		put_pixel(data, stripe, y, color);
}

void	place_pixel(t_sprite_data *s_data, t_data *data, int stripe)
{
	int				y;
	double			num;

	while (stripe < s_data->drawend_x)
	{
		y = s_data->drawstart_y;
		while (y < s_data->drawend_y && stripe > 0 && \
		stripe < data->map_data->dem_x)
		{
			num = ((double)data->textures->sprite->width / \
			(double)s_data->sprite_width);
			s_data->tex_x = (stripe - (-s_data->sprite_width / 2 + \
			s_data->spritescreen_x)) * num;
			if (s_data->trans_y > 0 && s_data->trans_y < \
				data->dda->buffer[stripe])
			{
				sprite_pixel(data, s_data, stripe, y);
			}
			y++;
		}
		stripe++;
	}
}

void	project_sprites(t_data *data, int *order)
{
	t_sprite_data	*s_data;
	int				i;
	int				stripe;

	i = 0;
	s_data = malloc(sizeof(t_sprite_data));
	while (i < data->map_data->amouth_of_sprites)
	{
		s_data = get_info(s_data, data, data->map_data->spr[order[i]]);
		s_data = sprite_start_end(data, s_data);
		stripe = s_data->drawstart_x;
		place_pixel(s_data, data, stripe);
		i++;
	}
}
