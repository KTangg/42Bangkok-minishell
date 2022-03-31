/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 01:16:54 by tratanat          #+#    #+#             */
/*   Updated: 2022/02/16 22:51:13 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	checkset(char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*out;
	int		len;
	int		out_len;

	i = 0;
	len = ft_strlen(s1) - 1;
	while (checkset(s1[len], set) && len >= 0)
		len--;
	len++;
	while (checkset(s1[i], set) && s1[i])
		i++;
	if (len <= i)
		out_len = 0;
	else
		out_len = len - i;
	out = (char *)malloc((out_len + 1) * sizeof(char));
	while (i < len + 1)
	{
		out[i - (len - out_len)] = s1[i];
		i++;
	}
	out[out_len] = '\0';
	return (out);
}

int	checkset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (c != set[i] && i < ft_strlen(set))
		i++;
	if (i >= ft_strlen(set))
		return (0);
	if (c == set[i])
		return (1);
	return (0);
}
