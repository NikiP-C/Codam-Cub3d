/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_error_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 20:26:51 by nphilipp       #+#    #+#                */
/*   Updated: 2020/03/05 17:07:08 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void	print_error_extra(int error_code)
{
	if (error_code == 9)
		write(1, "ERROR\nNo map found.\n", 20);
	else if (error_code == 10)
		write(1, "ERROR\nColor value is not between 0 and 255\n", 43);
	else if (error_code == 11)
		write(1, "ERROR\nWrong filetype for texture image\n", 39);
	else if (error_code == 12)
		write(1, "ERROR\nFailed to open texture image\n", 35);
	else if (error_code == 13)
		write(1, "ERROR\nExtra character found after color\n", 40);
	else if (error_code == 14)
		write(1, "ERROR\nFailed to initialize MLX window\n", 39);
	else if (error_code == 15)
		write(1, "ERROR\nFailed to initialize MLX image\n", 38);
	else if (error_code == 16)
		write(2, "ERROR\nMemory allocation fail\n", 29);
	else if (error_code == 17)
		write(2, "ERROR\nSecond argument is not --save\n", 37);
	else if (error_code == 18)
		write(2, "ERROR\nArgument count is not 2 or 3\n", 35);
	else if (error_code == 19)
		write(2, "ERROR\nOne of your elements is declared twice\n", 45);
	else if (error_code == 20)
		write(2, "ERROR\nOne of the dimensions is bigger then 16384\n", 49);
}

int			print_error(int error_code, char c)
{
	if (error_code == 1)
		write(2, "ERROR\nFormatting of map is incorrect\n", 38);
	else if (error_code == 2)
		write(2, "ERROR\nMore then one starting position found\n", 44);
	else if (error_code == 3)
	{
		write(2, "ERROR\nCharater |", 16);
		write(2, &c, 1);
		write(2, "| found, which is not a valid character\n", 40);
	}
	else if (error_code == 4)
		write(2, "ERROR\nNo player position found\n", 31);
	else if (error_code == 5)
		write(2, "ERROR\nOne or both of the dimensions are 0 or lower\n", 51);
	else if (error_code == 6)
		write(2, "ERROR\nCharacters found after the map\n", 37);
	else if (error_code == 7)
		write(2, "ERROR\nMap isn't fully inclosed in 1's\n", 38);
	else if (error_code == 8)
		write(2, "ERROR\nFile wasn't able to be opened.\n", 37);
	else
		print_error_extra(error_code);
	return (0);
}

int			error_missing(int error_code)
{
	if (error_code == 'R')
		write(2, "ERROR\nMissing resolution\n", 25);
	if (error_code == 'C')
		write(2, "ERROR\nMissing clg texture/color\n", 32);
	else if (error_code == 'F')
		write(2, "ERROR\nMissing floor texture/color\n", 34);
	else if (error_code == 'N')
		write(2, "ERROR\nMissing north texture\n", 28);
	else if (error_code == 'S')
		write(2, "ERROR\nMissing south texture\n", 28);
	else if (error_code == 'E')
		write(2, "ERROR\nMissing east texture\n", 27);
	else if (error_code == 'W')
		write(2, "ERROR\nMissing west texture\n", 27);
	else if (error_code == 'P')
		write(2, "ERROR\nMissing sprite texture\n", 29);
	else if (error_code == 'B')
		write(2, "ERROR\nOne of the RGB colors is missing\n", 39);
	return (1);
}
