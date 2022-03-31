/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:14:52 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/03 21:28:04 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "ft_printf_bonus.h"

int	get_flags(const char *str, va_list arg_ptr)
{
	int	offset;
	int	precision;

	offset = assign_flags(str, arg_ptr);
	str = str + offset;
	if (*str == '.')
	{
		if (*(str + 1) == '*')
		{
			precision = get_wildcard(arg_ptr);
			if (precision > 0)
				p_precision(precision);
			printf_flags(2);
			return (offset + 2);
		}
		offset++;
		printf_flags(2);
		precision = ft_atoi(++str);
		if (precision > 0)
			p_precision(precision);
		if (ft_isdigit(*str))
			offset += getdigit(precision);
	}
	return (offset);
}

// Flags =	[5:numeric_sign][4:prepend_space][3:hex_prefix]
//			[2:precision][1:prepend_zero][0:left-align]
int	assign_flags(const char *str, va_list arg_ptr)
{
	int	flag_res;
	int	offset;
	int	width;

	offset = 0;
	printf_flags(-2);
	flag_res = check_flags(*str);
	while (flag_res >= 0)
	{
		printf_flags(flag_res);
		flag_res = check_flags(*(++str));
		offset++;
	}
	width = ft_atoi(str);
	if (*str == '*')
		width = get_wildcard(arg_ptr);
	if (*str == '*')
		offset += 1;
	if (width)
	{
		printf_flags((width << 6));
		if (*str != '*')
			offset += getdigit(width);
	}
	return (offset);
}

int	printf_flags(int flag)
{
	static int	form_flags = 0;

	if (flag == -2)
		form_flags = 0;
	if (flag >= 0 && flag < 6)
		form_flags = form_flags | (1 << flag);
	else if (flag >= 6)
		form_flags = form_flags | flag;
	else if (flag == -1)
		return (form_flags);
	return (0);
}

int	check_flags(char c)
{
	if (c == '-')
		return (0);
	if (c == '0')
		return (1);
	if (c == '#')
		return (3);
	if (c == ' ')
		return (4);
	if (c == '+')
		return (5);
	return (-1);
}

int	p_precision(int precision)
{
	static int	form_precision = 0;

	if (precision == -1)
		return (form_precision);
	form_precision = precision;
	return (0);
}
