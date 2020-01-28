/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nphilipp <nphilipp@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 14:44:36 by nphilipp       #+#    #+#                */
/*   Updated: 2020/01/27 14:55:09 by nphilipp      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*str2;

	str2 = s;
	i = 0;
	while (i < n)
	{
		str2[i] = 0;
		i++;
	}
}

void		*ft_calloc(size_t count, size_t size)
{
	char	*str;

	str = malloc(size * count);
	if (str == 0)
		return (0);
	ft_bzero(str, size * count);
	return (str);
}