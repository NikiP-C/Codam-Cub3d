/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cud3d_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 14:00:39 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/13 12:49:40 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cud3d.h"

char	*ft_realloc(char *str, int malloc_size)
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = malloc(malloc_size);
	while (str[i])
	{
		newstr[i] = str[i];
		i++;
	}
	free(str);
	return (newstr);
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	int pos;

	if (x >= 0 && x < data->map_data->dem_x && y >= 0 && y < data->map_data->dem_y)
	{
		pos = y * data->mlx_data->line_lenght + x * (data->mlx_data->bits_per_pixel / 8);
		*(unsigned int *)(data->mlx_data->mlx_addr + pos) = color;
	}
}
