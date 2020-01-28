/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_minimap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 17:07:37 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/22 17:12:09 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cud3d.h"

void	mini_map(t_data *data)
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;

	img = mlx_new_image(data->mlx_data->mlx, data->map_data->dem_x / 10, data->map_data->dem_y / 10);
	addr = mlx_get_data_addr()
}