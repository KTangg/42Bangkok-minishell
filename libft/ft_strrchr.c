/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 00:07:32 by tratanat          #+#    #+#             */
/*   Updated: 2022/02/16 00:07:32 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0 && (unsigned char)s[i] != (unsigned char)c)
		i--;
	if (i < 0)
		return (NULL);
	if ((unsigned char)s[i] == (unsigned char)c)
		return ((char *)(s + i));
	else
		return (NULL);
}
