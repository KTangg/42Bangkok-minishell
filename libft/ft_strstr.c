/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:33:38 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/20 21:49:50 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char	*hay, char *needle)
{
	int	hay_len;
	int	needle_len;
	int	i;
	int	j;

	i = 0;
	hay_len = ft_strlen(hay);
	needle_len = ft_strlen(needle);
	while (i + needle_len <= hay_len)
	{
		j = 0;
		if (hay[i] == needle[j])
		{
			while (j < needle_len && hay[i + j] == needle[j])
				j++;
			if (j == needle_len)
				return (hay + i);
		}
		i++;
	}
	return (NULL);
}
