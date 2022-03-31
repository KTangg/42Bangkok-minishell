/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:30:17 by tratanat          #+#    #+#             */
/*   Updated: 2022/02/20 16:14:35 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	getdigit_u(unsigned int n);

char	*ft_itoa_u(unsigned int n)
{
	int				digit;
	char			*out;
	int				i;

	digit = getdigit_u(n);
	out = (char *)malloc((digit + 1) * sizeof(char));
	if (!out)
		return (NULL);
	i = digit;
	out[i--] = '\0';
	while (i >= 0)
	{
		out[i--] = '0' + (n % 10);
		n /= 10;
	}
	return (out);
}

int	getdigit_u(unsigned int n)
{
	int	digit;

	digit = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}
