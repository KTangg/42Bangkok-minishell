/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_padding_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 09:05:47 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/03 21:35:14 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "ft_printf_bonus.h"

void	padding_space(char *output, int padding)
{
	if (!(printf_flags(-1) & 1))
		while (padding-- > p_precision(-1))
			write(1, " ", 1);
	ft_putstr_fd(output, 1);
	if (printf_flags(-1) & 1)
		while (padding-- > p_precision(-1))
			write(1, " ", 1);
}

void	prepad_hex(int flags, int padding, const char *prefix, int precision)
{
	if (!(flags & 1))
	{
		if (flags & (1 << 3))
		{
			padding -= 2;
			if (!(flags & (1 << 1)) || (flags & (1 << 2)))
				while (padding-- > 0)
					write(1, " ", 1);
			write(1, prefix, ft_strlen(prefix));
			while (padding-- > 0)
				write(1, "0", 1);
		}
		else
		{
			while ((!(flags & (1 << 1)) || (flags & (1 << 2))) && padding-- > 0)
				write(1, " ", 1);
			while (padding-- > 0)
				write(1, "0", 1);
		}
	}
	else if (flags & (1 << 3))
		write(1, prefix, ft_strlen(prefix));
	while (precision-- > 0)
		write(1, "0", 1);
}

void	prepad_num(int flags, int padding, int positive, int precision)
{
	const char	sign[3] = "-+ ";

	if (flags & (1 << 5) && (flags & (1 << 1)))
		write(1, &sign[positive], 1);
	else if (flags & (1 << 4) && (flags & (1 << 1)))
		write(1, &sign[positive * 2], 1);
	else if (!positive && (flags & (1 << 1)) && !(flags & (1 << 2)))
		write(1, &sign[positive], 1);
	padding -= (!positive || flags & (1 << 5) || flags & (1 << 4));
	while (padding-- > 0)
	{
		if (flags & (1 << 1) && !(flags & (1 << 2)) && !(flags & 1))
			write(1, "0", 1);
		else if (!(flags & 1))
			write(1, " ", 1);
	}
	if (flags & (1 << 5) && !(flags & (1 << 1)))
		write(1, &sign[positive], 1);
	else if (flags & (1 << 4) && !(flags & (1 << 1)))
		write(1, &sign[positive * 2], 1);
	else if (!positive && (!(flags & (1 << 1)) || (flags & (1 << 2))))
		write(1, &sign[positive], 1);
	while (precision-- > 0)
		write(1, "0", 1);
}

int	ft_intpadding(long int *num, char *output, int *padding, int *pos)
{
	int	length;
	int	flags;

	if (*num < 0)
		*pos = 0;
	if (*num < 0)
		*num = -(*num);
	flags = printf_flags(-1);
	length = ft_strlen(output);
	if ((flags & (1 << 2)) && p_precision(-1) > length)
		length = p_precision(-1);
	if ((flags >> 6) > length)
		*padding = (printf_flags(-1) >> 6) - length;
	else
		length += !!((flags & (1 << 4)) || (flags & (1 << 5)) || !(*pos));
	if ((flags & (1 << 2)) || (flags & (1 << 1)) || !(flags & 1))
		prepad_num(flags, *padding, *pos, p_precision(-1) - ft_strlen(output));
	else
		prepad_num(flags, 0, *pos, p_precision(-1) - ft_strlen(output));
	return (length);
}
