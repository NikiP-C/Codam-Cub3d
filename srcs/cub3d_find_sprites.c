/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_find_sprites.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/21 15:35:06 by nphilipp       #+#    #+#                */
/*   Updated: 2020/03/01 17:11:35 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	fill_sprite_data(t_vs *spr, char c, int i, int j)
{
	spr->x = (double)(i + 0.5);
	spr->y = (double)(j + 0.5);
	spr->sprite = c;
}

void		find_sprites(t_map_data *data)
{
	int		j;
	int		i;
	int		l;

	j = 0;
	l = 0;
	if (data->amouth_of_sprites == 0)
		return ;
	data->spr = ft_calloc(data->amouth_of_sprites, sizeof(t_vs));
	if (data->spr == NULL)
		exit(print_error(16, 0));
	while (data->map2d[j] != NULL)
	{
		i = 0;
		while (data->map2d[j][i] != '\0')
		{
			if (data->map2d[j][i] == '2')
			{
				fill_sprite_data(&data->spr[l], data->map2d[j][i], i, j);
				l++;
			}
			i++;
		}
		j++;
	}
}
