/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:25:27 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/02 16:43:28 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>

int		ft_printf(const char *str, ...);
int		ft_printarg(const char flag, va_list arg_ptr);
char	*ft_itoa_u(unsigned int n);
int		ft_putnbr_u(unsigned int n, int fd);
char	*ft_itoa_base(unsigned long long int n, int base);
int		ft_printhex_up(long int ptr);
int		ft_printhex_low(long int ptr);
int		ft_printadd_hex(void *ptr);
int		getdigit_base(unsigned long long int n, int base);

#endif