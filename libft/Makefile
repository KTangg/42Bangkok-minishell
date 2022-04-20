# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/15 23:45:11 by tratanat          #+#    #+#              #
#    Updated: 2022/04/20 21:34:11 by tratanat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c	\
	ft_bzero.c	\
	ft_calloc.c	\
	ft_isalnum.c	\
	ft_isalpha.c	\
	ft_isascii.c	\
	ft_isdigit.c	\
	ft_isprint.c	\
	ft_itoa.c	\
	ft_memchr.c	\
	ft_memcmp.c	\
	ft_memcpy.c	\
	ft_memmove.c	\
	ft_memset.c	\
	ft_putchar_fd.c	\
	ft_putendl_fd.c	\
	ft_putnbr_fd.c	\
	ft_putstr_fd.c	\
	ft_split.c	\
	ft_strchr.c	\
	ft_strdup.c	\
	ft_striteri.c	\
	ft_strjoin.c	\
	ft_strlcat.c	\
	ft_strlcpy.c	\
	ft_strlen.c	\
	ft_strmapi.c	\
	ft_strncmp.c	\
	ft_strnstr.c	\
	ft_strrchr.c	\
	ft_strtrim.c	\
	ft_substr.c	\
	ft_tolower.c	\
	ft_toupper.c	\
	ft_lstadd_back.c	\
	ft_lstadd_front.c	\
	ft_lstclear.c	\
	ft_lstdelone.c	\
	ft_lstiter.c	\
	ft_lstlast.c	\
	ft_lstmap.c	\
	ft_lstnew.c	\
	ft_lstsize.c	\
	ft_printf.c	\
	ft_printftype.c	\
	ft_flagformat.c	\
	ft_printf_padding.c	\
	ft_printf_flags.c	\
	ft_itoa_base.c	\
	ft_itoa_u.c	\
	get_next_line.c	\
	get_next_line_utils.c	\
	ft_strcmp.c	\
	ft_strstr.c

NAME = libft.a
CC = gcc -Wextra -Wall -Werror -std=c99

all: $(NAME)

$(NAME): $(SRCS) libft.h
	@$(CC) -c $(SRCS)
	@ar rcs $(NAME) *.o

clean:
	@rm -rf *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

