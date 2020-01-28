/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   2darray_printer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 17:54:34 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/21 17:59:59 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	twod_array_printer(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		write(1, array[i], ft_strlen(array[i]));
		write(1, "\n", 1);
		i++;
	}
}
