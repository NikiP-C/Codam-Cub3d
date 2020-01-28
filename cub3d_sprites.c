/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_sprites.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/16 18:41:27 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/27 21:07:28 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"

t_sprite_data	*sprite_start_end(t_data *data, t_sprite_data *s_data)
{
	s_data->sprite_height = (int)data->map_data->dem_y / s_data->trans_y;
	if (s_data->sprite_height < 0)
		s_data->sprite_height *= -1;
	s_data->drawstart_y = -s_data->sprite_height \
	/ 2 + data->map_data->dem_y / 2;
	if (s_data->drawstart_y < 0)
		s_data->drawstart_y = 0;
	s_data->drawend_y = s_data->sprite_height / 2  + data->map_data->dem_y / 2;
	if (s_data->drawend_y >= data->map_data->dem_y)
		s_data->drawend_y = data->map_data->dem_y - 1;
	s_data->sprite_width = (int)data->map_data->dem_y / s_data->trans_y;
	if (s_data->sprite_width < 0)
		s_data->sprite_width *= -1;
	s_data->drawstart_x = -s_data->sprite_width / 2 + s_data->spritescreen_x;
	if (s_data->drawstart_x < 0)
		s_data->drawstart_x = 0;
	s_data->drawend_x = s_data->sprite_width / 2  + s_data->spritescreen_x;
	if (s_data->drawend_x >= data->map_data->dem_x)
		s_data->drawend_x = data->map_data->dem_x - 1;
	return (s_data);
}

t_sprite_data	*get_info(t_sprite_data *s_data, t_data *data, t_sprite *tmp)
{
	s_data->sprite_x = tmp->x - data->map_data->pos_x;
	s_data->sprite_y = tmp->y - data->map_data->pos_y;
	s_data->invdet = 1.0 / (data->map_data->plane_x * data->map_data->dir_y\
	- data->map_data->dir_x * data->map_data->plane_y);
	s_data->trans_x = s_data->invdet * (data->map_data->dir_y \
	* s_data->sprite_x - data->map_data->dir_x * s_data->sprite_y);
	s_data->trans_y = s_data->invdet * (-data->map_data->plane_y\
	* s_data->sprite_x + data->map_data->plane_x * s_data->sprite_y);
	s_data->spritescreen_x = (int)((data->map_data->dem_x / 2) *\
	(1 + s_data->trans_x / s_data->trans_y));
	return (s_data);
}

void	place_pixel(t_sprite_data *s_data, t_data *data, int stripe)
{
	char			*test;
	unsigned int	color;
	int				y;
	double			num;

	while (stripe < s_data->drawend_x)
	{
		y = s_data->drawstart_y;
		while (y < s_data->drawend_y)
		{
			s_data->tex_x = (stripe - (-s_data->sprite_width / 2 + \
			s_data->spritescreen_x)) * num;
			if (s_data->trans_y > 0 && stripe > 0 && \
				stripe < data->map_data->dem_x && \
					s_data->trans_y <= data->dda->buffer[stripe])
				num = ((double)data->textures->sprite->width / \
				(double)s_data->sprite_width);
			s_data->d = (y) * 256 - data->map_data->dem_y * 128 + s_data->sprite_height * 128;
			s_data->tex_y = ((s_data->d * data->textures->sprite->height) / s_data->sprite_height) / 256;
			test = data->textures->sprite->img_addr + (data->textures->sprite->size_line * s_data->tex_y) + s_data->tex_x * (data->textures->sprite->bits_per_pixel / 8);
			color = *((unsigned int *)test);
			if ((color & 0x00FFFFFF) != 0)
				put_pixel(data, stripe, y, color);
			y++;
		}
		stripe++;
	}
}

void	project_sprites(t_data *data)
{
	t_sprite		*tmp;
	t_sprite_data	*s_data;
	int				i;
	int				stripe;
	double			num;

	i = 0;
	s_data = malloc(sizeof(t_sprite_data));
	tmp = data->map_data->sprite;
	while (tmp != NULL)
	{
		printf("A\n");
		s_data = get_info(s_data, data, tmp);
		s_data = sprite_start_end(data, s_data);
		stripe = s_data->drawstart_x;
		place_pixel(s_data, data, stripe);
		tmp = tmp->next;
		i++;
	}
}

int		is_sorted(t_sprite *head)
{
	t_sprite *tmp;

	tmp = head;
	if (tmp == NULL)
		return (0);
	while (tmp->next != NULL)
	{
		printf("sa\n");
		if (tmp->distance < tmp->next->distance)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	sort_sprites(t_sprite **head)
{
	t_sprite *current;
	t_sprite *next;
	t_sprite *previous;
	
	if (*head == NULL)
		return ;
	while (is_sorted(*head))
	{
		printf("FIRST LOOP\n");
		current = *head;
		next = (*head)->next;
		printf("hoi\n");
		while (next != NULL && current != NULL)
		{
			if (current->distance < next->distance)
			{
				previous->next = next;
				current->next = next->next;
				next->next = current;
				printf("IF\n");
			}
			previous = current;
			current = next;
			next = next->next;
			printf("SECOND LOOP\n");
		}
	}
	return ;
}

void	get_distance(t_data *data, t_sprite **head)
{
	t_sprite *tmp;

	tmp = *head;
	while (tmp != NULL)
	{
		printf("llll\n");
		tmp->distance = (data->map_data->pos_x - tmp->x) * \
		(data->map_data->pos_x - tmp->x) + (data->map_data->pos_y - tmp->y)\
		* (data->map_data->pos_y - tmp->y);
		tmp = tmp->next;
	}
}

void	clear_sprites(t_sprite *sprite)
{
	t_sprite *tmp;
	
	tmp = sprite;
	while (tmp != NULL)
	{
		tmp->distance = 0;
		tmp = tmp->next;
	}
}

t_data	*sprites(t_data *data)
{
	printf("ccc\n");
	get_distance(data, &data->map_data->sprite);
	printf("aaa\n");
	sort_sprites(&data->map_data->sprite);
	printf("bbb\n");
	project_sprites(data);
	clear_sprites(data->map_data->sprite);
	return (data);
}
