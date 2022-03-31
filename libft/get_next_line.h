/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 09:34:32 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/05 01:02:41 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_storedlst
{
	int					fd;
	char				*stored;
	struct s_storedlst	*next;
}	t_storedlst;

# define BUFFER_SIZE 1

char	*get_next_line(int fd);
int		checknl(char **output, char *buffer, int fd, t_storedlst **readlst);
int		storeline(char *buffer, int fd, t_storedlst **readlst);
int		getstored(t_storedlst **readlst, char **output, int fd);
char	*ft_strnjoin(char *dst, char *src, int n);
void	ft_lstdel(t_storedlst **readlst, t_storedlst *target);
char	*ft_strdupgnl(char *src);

#endif
