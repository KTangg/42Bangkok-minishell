/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:17:37 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/03 21:17:37 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "ft_printf_bonus.h"

int	ft_printf(const char *str, ...)
{
	va_list	arg_ptr;
	int		length;
	int		flag_offset;

	length = 0;
	va_start(arg_ptr, str);
	while (*str)
	{
		if (*str == '%')
		{
			p_precision(0);
			printf_flags(-2);
			flag_offset = get_flags(++str, arg_ptr);
			str = str + flag_offset;
			length += ft_printarg(*str, arg_ptr);
			str++;
			continue ;
		}
		write(1, str, 1);
		length++;
		str++;
	}
	va_end(arg_ptr);
	return (length);
}

int	ft_printarg(const char flag, va_list arg_ptr)
{
	if (flag == 'c')
		return (printf_char(va_arg(arg_ptr, int)));
	else if (flag == 's')
		return (printf_string(va_arg(arg_ptr, char *)));
	else if (flag == 'p')
		return (ft_printadd_hex(va_arg(arg_ptr, void *)));
	else if (flag == 'd' || flag == 'i')
		return (ft_printint(va_arg(arg_ptr, int)));
	else if (flag == 'u')
		return (ft_putnbr_u(va_arg(arg_ptr, unsigned int), 1));
	else if (flag == 'x')
		return (ft_printhex_low(va_arg(arg_ptr, long int)));
	else if (flag == 'X')
		return (ft_printhex_up(va_arg(arg_ptr, long int)));
	else if (flag == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	return (0);
}

int	get_wildcard(va_list arg_ptr)
{
	int	rtn;

	rtn = va_arg(arg_ptr, int);
	if (rtn < 0)
	{
		printf_flags(0);
		rtn = -rtn;
	}
	return (rtn);
}
