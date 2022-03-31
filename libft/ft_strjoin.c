/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 01:17:03 by tratanat          #+#    #+#             */
/*   Updated: 2022/02/15 01:17:03 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*out;
	int		i;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	out = (char *)malloc((len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	while (i < len && s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	while (i < len && *s2)
	{
		out[i] = *s2;
		i++;
		s2++;
	}
	out[i] = '\0';
	return (out);
}
