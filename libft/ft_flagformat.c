/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagformat_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 21:39:08 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/03 21:35:15 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_bonus.h"
#include "libft.h"

int	printf_string(char *result)
{
	int		length;
	int		padding;
	char	*output;
	int		isnull;

	isnull = !(result);
	if (result == 0)
		result = ft_strdup("(null)");
	if (p_precision(-1) < (int)ft_strlen(result) && printf_flags(-1) & (1 << 2))
		length = p_precision(-1);
	else
		length = ft_strlen(result);
	output = (char *)ft_calloc((length + 1), sizeof(char));
	ft_strlcpy(output, result, length + 1);
	padding = 0;
	if ((printf_flags(-1) >> 6) > length)
		padding = (printf_flags(-1) >> 6) - length;
	length += padding;
	padding_space(output, padding + p_precision(-1));
	if (isnull == 1)
		free(result);
	free(output);
	return (length);
}

int	printf_char(int c)
{
	int	length;
	int	left_aligned;
	int	min_width;
	int	flags;
	int	padding;

	flags = printf_flags(-1);
	min_width = flags >> 6;
	left_aligned = flags & 1;
	padding = 0;
	if (min_width > 1)
		padding = min_width - 1;
	length = 1 + padding;
	if (!left_aligned)
		while (padding--)
			write(1, " ", 1);
	ft_putchar_fd(c, 1);
	if (left_aligned)
		while (padding--)
			write(1, " ", 1);
	return (length);
}

int	printf_hex(char *result, int upper)
{
	int	min_width;
	int	flags;
	int	padding;
	int	length;

	flags = printf_flags(-1);
	min_width = flags >> 6;
	padding = 0;
	length = ft_strlen(result);
	if (p_precision(-1) > (int)ft_strlen(result))
		length = p_precision(-1);
	if (min_width > length)
		padding = min_width - length;
	if ((flags & (1 << 3)) && padding == 0 && *result != '0')
		padding = 2;
	length += padding;
	if (upper)
		prepad_hex(flags, padding, "0X", p_precision(-1) - ft_strlen(result));
	else
		prepad_hex(flags, padding, "0x", p_precision(-1) - ft_strlen(result));
	if (!((p_precision(-1) == 0) && (flags & (1 << 2)) && *result == '0'))
		ft_putstr_fd(result, 1);
	while ((padding-- > ((flags & (1 << 3)) * 2)) && (flags & 1))
		write(1, " ", 1);
	return (length);
}

int	ft_putnbr_u(unsigned int n, int fd)
{
	char	*out;
	int		digits;
	int		i;
	int		padding;
	int		flags;

	if (n == 0)
		return (ft_printf_numzero());
	i = -1;
	flags = printf_flags(-1);
	out = ft_itoa_u(n);
	digits = ft_strlen(out);
	if ((flags & (1 << 2)) && (p_precision(-1) > digits))
		digits = p_precision(-1);
	padding = ((flags >> 6) > digits) * ((flags >> 6) - digits);
	if (!(flags & 1) || (flags & (1 << 2)))
		prepad_num(flags, padding, 1, digits - ft_strlen(out));
	while (++i < (int)ft_strlen(out))
		write(fd, out + i, 1);
	i += (digits - ft_strlen(out)) + padding;
	while (padding-- > 0 && (flags & 1))
		write(1, " ", 1);
	free(out);
	return (i);
}

int	ft_printint(long int n)
{
	int		pos;
	char	*output;
	int		padding;
	int		length;
	int		flags;

	pos = 1;
	padding = 0;
	flags = printf_flags(-1);
	if (n == 0 && !(flags & (1 << 5)) && !(flags & (1 << 4)))
		return (ft_printf_numzero());
	output = ft_itoa(ft_abs(n));
	length = ft_intpadding(&n, output, &padding, &pos);
	if (n != 0 || (!(flags & (1 << 2)) || ((p_precision(-1) > 0) && n == 0)))
		ft_putstr_fd(output, 1);
	else if (n == 0 && p_precision(-1) == 0 && (flags >> 6) > 0)
		write(1, " ", 1);
	free(output);
	length += padding;
	if (flags & 1)
		while ((padding-- > !pos || flags & (1 << 5) || flags & (1 << 4)))
			write(1, " ", 1);
	return (length);
}
