/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 23:59:27 by tratanat          #+#    #+#             */
/*   Updated: 2022/02/15 23:59:27 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		length;
	char	*out;
	int		i;

	i = 0;
	length = ft_strlen(str);
	out = (char *)malloc((length + 1) * sizeof(char));
	while (str[i])
	{
		out[i] = str[i];
		i++;
	}
	out[i] = str[i];
	return (out);
}
