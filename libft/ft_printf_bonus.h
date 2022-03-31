/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:59:58 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/03 20:35:07 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

int		assign_flags(const char *str, va_list arg_ptr);
int		printf_flags(int flag);
int		check_flags(char c);
int		printf_string(char *result);
int		printf_hex(char *result, int upper);
void	prepad_hex(int flags, int padding, const char *prefix, int precision);
void	prepad_num(int flags, int padding, int positive, int precision);
int		printf_char(int c);
int		get_flags(const char *str, va_list arg_ptr);
int		p_precision(int precision);
void	padding_space(char *output, int padding);
int		ft_printint(long int num);
int		ft_printf_numzero(void);
int		check_zero_return(void);
int		ft_intpadding(long int *num, char *output, int *padding, int *pos);
int		get_wildcard(va_list arg_ptr);

#endif
