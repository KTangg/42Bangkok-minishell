/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printftype_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 22:42:22 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/03 15:57:23 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "ft_printf_bonus.h"

int	ft_printadd_hex(void *ptr)
{
	char	*out;
	int		printlen;
	int		padding;

	printlen = !!(ptr) * 2;
	if (ptr == NULL)
		out = ft_strdup("0x0");
	else
		out = ft_itoa_base((unsigned long long int)ptr, 16);
	printlen += ft_strlen(out);
	padding = 0;
	if ((printf_flags(-1) >> 6) > printlen)
		padding = (printf_flags(-1) >> 6) - printlen;
	if ((printf_flags(-1) >> 6) > printlen)
		printlen = printf_flags(-1) >> 6;
	if (!(printf_flags(-1) & 1) && padding > 0)
		while (padding-- > 0)
			write(1, " ", 1);
	if (ft_strncmp(out, "0x0", 4))
		write(1, "0x", 2);
	ft_putstr_fd(out, 1);
	while (padding-- > 0)
		write(1, " ", 1);
	free(out);
	return (printlen);
}

int	ft_printhex_low(long int ptr)
{
	unsigned int	hex;
	char			*result;
	int				length;

	if (ptr == 0)
		return (ft_printf_numzero());
	if (ptr < 0)
		hex = (unsigned long int)(((-ptr) ^ 0xFFFFFFFF) + 1);
	else
		hex = (unsigned long int)ptr;
	result = ft_itoa_base(hex, 16);
	if (*result == '0' && ft_strlen(result) == 1)
	{
		free(result);
		return (ft_printf_numzero());
	}
	length = printf_hex(result, 0);
	free(result);
	return (length);
}

int	ft_printhex_up(long int ptr)
{
	unsigned int	hex;
	char			*result;
	size_t			i;
	int				length;

	if (ptr == 0)
		return (ft_printf_numzero());
	if (ptr < 0)
		hex = (unsigned long int)(((-ptr) ^ 0xFFFFFFFF) + 1);
	else
		hex = (unsigned long int)ptr;
	result = ft_itoa_base(hex, 16);
	if (*result == '0' && ft_strlen(result) == 1)
	{
		free(result);
		return (ft_printf_numzero());
	}
	i = -1;
	while (++i < ft_strlen(result))
		result[i] = ft_toupper(result[i]);
	length = printf_hex(result, 1);
	free(result);
	return (length);
}

int	ft_printf_numzero(void)
{
	int	padding;
	int	i;

	i = 0;
	padding = printf_flags(-1) >> 6;
	if ((printf_flags(-1) & (1 << 2)) || printf_flags(-1) & (1 << 1))
	{
		if (printf_flags(-1) & (1 << 2))
			while (i++ < padding - p_precision(-1))
				write(1, " ", 1);
		else
			while (i++ < padding - 1)
				write(1, "0", 1);
		i = 0;
		while (i++ < p_precision(-1))
			write(1, "0", 1);
		if (p_precision(-1) == 0 && !(printf_flags(-1) & (1 << 2)))
			write(1, "0", 1);
	}
	else
		padding_space("0", padding - 1);
	return (check_zero_return());
}

int	check_zero_return(void)
{
	int	prec;
	int	flags;

	flags = printf_flags(-1);
	prec = p_precision(-1);
	if ((flags & (1 << 2)) && prec > (flags >> 6))
		return (prec);
	else if ((flags & (1 << 2)) && p_precision(-1) == 0)
		return (flags >> 6);
	else if (!(flags & (1 << 2)) && (flags >> 6) == 0)
		return (1);
	return (flags >> 6);
}
