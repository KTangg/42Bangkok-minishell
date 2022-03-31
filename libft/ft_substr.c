/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 01:17:12 by tratanat          #+#    #+#             */
/*   Updated: 2022/02/15 01:17:12 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	int		length;
	char	*out;

	i = 0;
	length = len;
	if ((start + len - 1) >= (unsigned int)ft_strlen(s))
		length = length - start;
	out = (char *)malloc((length + 1) * sizeof(char));
	if (!out)
		return (NULL);
	while (i < length)
	{
		out[i] = s[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
