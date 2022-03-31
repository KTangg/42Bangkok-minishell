/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 00:05:23 by tratanat          #+#    #+#             */
/*   Updated: 2022/02/16 00:05:23 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	length;

	length = 0;
	if (!dst || !src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	while (*src && length < dstsize - 1)
	{
		*dst = *src;
		src++;
		dst++;
		length++;
	}
	if (*src)
	{
		while (*src)
		{
			length++;
			src++;
		}
	}
	*dst = '\0';
	return (length);
}
