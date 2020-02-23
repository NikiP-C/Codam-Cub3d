/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_project_sprites.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 23:17:09 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/22 16:39:36 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sprite_pixel(t_data *data, t_sprite_data *s_data, \
				t_vsi *coords, t_texture *sprite)
{
	unsigned int	color;
	char			*test;

	(*s_data).d = ((*coords).y) * 256 - (*data).map_data.dem_y * \
		128 + (*s_data).sprite_height * 128;
	(*s_data).tex_y = (((*s_data).d * (*sprite).height) \
		/ (*s_data).sprite_height) / 256;
	test = (*sprite).img_addr + ((*sprite).size_line * (*s_data).tex_y) \
		+ (*s_data).tex_x * ((*sprite).bits_per_pixel / 8);
	color = *((unsigned int *)test);
	if ((color & 0x00FFFFFF) != 0)
		put_pixel(data, (*coords).x, (*coords).y, color);
}

void	place_pixel(t_sprite_data *s_data, t_data *data, \
				t_vsi *coords, t_texture *sprite)
{
	double			num;

	while ((*coords).x < (*s_data).drawend_x)
	{
		(*coords).y = (*s_data).drawstart_y;
		while ((*coords).y < (*s_data).drawend_y && (*coords).x > 0 && \
		(*coords).x < (*data).map_data.dem_x)
		{
			num = ((double)((*sprite).width) / (double)(*s_data).sprite_width);
			(*s_data).tex_x = ((*coords).x - (-(*s_data).sprite_width / 2 + \
			(*s_data).spritescreen_x)) * num;
			if ((*s_data).trans_y > 0 && (*s_data).trans_y < \
					(*data).dda.buffer[(*coords).x])
			{
				sprite_pixel(data, s_data, coords, sprite);
			}
			(*coords).y++;
		}
		(*coords).x++;
	}
}

void	project_sprites(t_data *data, int *order)
{
	t_sprite_data	s_data;
	int				i;
	t_vsi			coords;

	i = 0;
	while (i < (*data).map_data.amouth_of_sprites)
	{
		get_info(&s_data, data, (*data).map_data.spr[order[i]]);
		sprite_start_end(data, &s_data);
		coords.x = s_data.drawstart_x;
		if ((*data).map_data.spr[order[i]].sprite == '2')
		{
			place_pixel(&s_data, data, &coords, &(*data).textures.sprite_1);
		}
		else
		{
			place_pixel(&s_data, data, &coords, &(*data).textures.sprite_2);
		}
		i++;
	}
}
