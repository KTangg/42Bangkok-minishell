/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:30:17 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/02 13:24:20 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

long int	ft_abs(long int n);

char	*ft_itoa(long int n)
{
	int				digit;
	int				negative;
	char			*out;
	int				i;
	long int		num;

	negative = 0;
	num = (ft_abs(n));
	if (n < 0)
		negative = 1;
	digit = getdigit(num);
	out = (char *)malloc((digit + negative + 1) * sizeof(char));
	if (!out)
		return (NULL);
	i = digit + negative;
	out[i--] = '\0';
	while (i >= negative)
	{
		out[i--] = '0' + (num % 10);
		num /= 10;
	}
	if (negative)
		out[0] = '-';
	return (out);
}

long int	ft_abs(long int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

int	getdigit(long int n)
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
