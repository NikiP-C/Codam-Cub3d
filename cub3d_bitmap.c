/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_bitmap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 17:42:33 by nphilipp       #+#    #+#                */
/*   Updated: 2020/02/21 14:43:58 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "cud3d.h"
#include <unistd.h>

char	*fill_zero(char *str, int start, int end)
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
	str[4] = (unsigned char)((*data).map_data.dem_x);
	str[5] = (unsigned char)((*data).map_data.dem_x >> 8);
	str[6] = (unsigned char)((*data).map_data.dem_x >> 16);
	str[7] = (unsigned char)((*data).map_data.dem_x >> 24);
	str[8] = (unsigned char)((*data).map_data.dem_y);
	str[9] = (unsigned char)((*data).map_data.dem_y >> 8);
	str[10] = (unsigned char)((*data).map_data.dem_y >> 16);
	str[11] = (unsigned char)((*data).map_data.dem_y >> 24);
	return (str);
}

void	zero_pad(int x, int fd)
{
	int		zero;
	char	null;

	null = 0;
	zero = 4 - ((x * 3) % 4);
	while (zero)
	{
		write(fd, &null, 1);
		zero--;
	}
}

void	make_image(t_data *data, int fd)
{
	int				y;
	int				x;
	char			*test;
	unsigned int	color;

	y = (*data).map_data.dem_y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < (*data).map_data.dem_x)
		{
			test = (*data).mlx_data.current_img->mlx_addr + \
			((*data).mlx_data.current_img->line_lenght \
				* y + (x * ((*data).mlx_data.current_img->bits_per_pixel / 8)));
			color = *((int *)test);
			write(fd, &color, 3);
			x++;
		}
		if ((x * 3) % 4 != 0)
			zero_pad(x, fd);
		y--;
	}
}

void	make_bitmap(t_data *data)
{
	int				fd;
	unsigned int	size;
	char			*fileheader;
	char			*infoheader;
	int				pad;

	fileheader = ft_calloc(14, sizeof(char));
	infoheader = ft_calloc(40, sizeof(char));
	if (fileheader == NULL || infoheader == NULL)
		exit(print_error(16, 0));
	pad = (4 - ((*data).map_data.dem_x * 3) % 4) * (*data).map_data.dem_y;
	size = (*data).map_data.dem_x * (*data).map_data.dem_y * 3 + 54 + pad;
	fd = open("img.bmp", O_WRONLY | O_CREAT, 0644);
	fileheader[0] = 'B';
	fileheader[1] = 'M';
	*((unsigned int *)(fileheader + 2)) = size;
	fileheader[10] = 54;
	infoheader = make_infoheader(data, infoheader);
	write(fd, fileheader, 14);
	free(fileheader);
	write(fd, infoheader, 40);
	free(infoheader);
	make_image(data, fd);
}
