/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cud3d_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/06 14:00:39 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/31 14:21:59 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cud3d.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	int pos;

	if (x >= 0 && x < data->map_data->dem_x && y >= 0\
	&& y < data->map_data->dem_y)
	{
		pos = y * data->mlx_data->line_lenght + x *\
		(data->mlx_data->bits_per_pixel / 8);
		*(unsigned int *)(data->mlx_data->mlx_addr + pos) = color;
	}
}

int		print_error(int error_code, char c)
{
	if (error_code == 1)
		write(1, "ERROR\nFormatting of map is incorrect\n", 38);
	else if (error_code == 2)
		write(1, "ERROR\nMore then one starting position found\n", 44);
	else if (error_code == 3)
	{
		write(1, "ERROR\nCharater |", 16);
		write(1, &c, 1);
		write(1, "| found, which is not a valid character\n", 40);
	}
	else if (error_code == 4)
		write(1, "ERROR\nNo player position found\n", 31);
	else if (error_code == 5)
		write(1, "ERROR\nBottom row doesn't contain only 1's\n", 42);
	else if (error_code == 6)
		write(1, "ERROR\nTop row doesn't contain only 1's\n", 39);
	else if (error_code == 7)
		write(1, "ERROR\nMap isn't fully inclosed in 1's\n", 38);
	else if (error_code == 8)
		write(1, "ERROR\nFile wasn't able to be opened.\n", 37);
	else if (error_code == 9)
		write(1, "ERROR\nNo map found.\n", 20);
	return (0);
}

char	*ft_realloc(char *str, int malloc_size)
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = ft_calloc(malloc_size, 1);
	while (str[i])
	{
		newstr[i] = str[i];
		i++;
	}
	free(str);
	return (newstr);
}

double	ft_abs(double num)
{
	if (num < 0)
		num *= -1;
	return (num);
}
