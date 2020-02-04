/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_bitmap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 17:42:33 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/04 11:52:36 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "cud3d.h"


char *fill_zero(char *str, int start, int end)
{
	while (start <= end)
	{
		str[start] = 0;
		start++;
	}
	return (str);
}

char	*make_infoheader(t_data *data, char *str)
{
	str[0] = 40;
	str[12] = 1;
	str[14] = 24;
	str[2] = (unsigned char)(data->map_data->dem_x);
	str[3] = (unsigned char)(data->map_data->dem_x>> 8);
	str[4] = (unsigned char)(data->map_data->dem_x>>16);
	str[5] = (unsigned char)(data->map_data->dem_x>>24);
	str[6] = (unsigned char)(data->map_data->dem_x);
	str[7] = (unsigned char)(data->map_data->dem_x>> 8);
	str[8] = (unsigned char)(data->map_data->dem_x>>16);
	str[9] = (unsigned char)(data->map_data->dem_x>>24);
	return (str);
}

void	make_rgb(unsigned int color, int fd)
{
	char c[3];

	if (color)
		;
	c[0] = (char)0;
	c[1] = (char)0;
	c[2] = (char)255;
	write(fd, c, 3);
}

void	make_image(t_data *data, int fd)
{
	int y;
	int x;
	int zero;
	char null;

	null = 0;
	y = data->map_data->dem_y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < data->map_data->dem_x)
		{
			make_rgb((unsigned int)data->mlx_data->mlx_addr + \
				(data->map_data->dem_y * y + x), fd);
			x++;
		}
		if ((x * 3) % 4 != 0)
		{
			zero = 4 - ((x * 3) % 4);
			while (zero)
			{
				write(fd, &null, 1);
				zero--;
			}
		}
		y--;
	}
}

void	make_bitmap(t_data *data)
{
	int 			fd;
	unsigned int	size;
	char			*fileheader;
	char			*infoheader;

	fileheader = malloc(sizeof(char) * 14);
	infoheader = malloc(sizeof(char) * 40);

	size = data->map_data->dem_x * data->map_data->dem_y * 3 + 54;
	fd = open("image_bmp.txt", O_WRONLY | O_CREAT, 0644);
	fileheader = fill_zero(fileheader, 0, 13);
	infoheader = fill_zero(infoheader, 0, 39);
	fileheader[0] = 'B';
	fileheader[1] = 'M';
	fileheader[2] = (unsigned char)(size);
	fileheader[3] = (unsigned char)(size>> 8);
	fileheader[4] = (unsigned char)(size>>16);
	fileheader[5] = (unsigned char)(size>>24);
	fileheader[10] = 54;
	infoheader = make_infoheader(data, infoheader);
	write(fd, fileheader, 14);
	free(fileheader);
	write(fd, infoheader, 40);
	free(infoheader);
	make_image(data, fd);
}
