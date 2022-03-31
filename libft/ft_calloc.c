/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 00:00:27 by tratanat          #+#    #+#             */
/*   Updated: 2022/02/16 00:00:27 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(int number, int size)
{
	void	*ptr;
	int		len;
	int		i;

	i = 0;
	ptr = malloc(number * size);
	len = number * size;
	while (i < len)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
