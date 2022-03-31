/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 00:05:44 by tratanat          #+#    #+#             */
/*   Updated: 2022/02/16 10:31:55 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	length;

	length = 0;
	while (*dst)
	{
		dst++;
		length++;
	}
	if (!(length < dstsize))
		return (ft_strlen(src) + dstsize);
	while (length < dstsize - 1 && *src)
	{
		*dst = *src;
		dst++;
		src++;
		length++;
	}
	*dst = '\0';
	return (length + ft_strlen(src));
}
