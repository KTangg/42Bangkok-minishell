/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:44:01 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/05 01:03:08 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(char *buffer, int size)
{
	int	i;

	i = 0;
	while (i < size)
		buffer[i++] = 0;
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

char	*ft_strnjoin(char *dst, char *src, int n)
{
	int		totallen;
	char	*output;
	int		i;

	i = 0;
	if (!dst)
		totallen = n;
	else
		totallen = ft_strlen(dst) + n;
	output = (char *)malloc((totallen + 1) * sizeof(char));
	while (dst && dst[i])
	{
		output[i] = dst[i];
		i++;
	}
	while (i < totallen)
	{
		output[i] = src[i - (totallen - n)];
		i++;
	}
	output[i] = '\0';
	if (dst)
		free(dst);
	return (output);
}

void	ft_lstdel(t_storedlst **readlst, t_storedlst *target)
{
	t_storedlst	*temp;
	t_storedlst	*cur;

	cur = *readlst;
	if (*readlst == target)
	{
		free(target);
		*readlst = NULL;
		return ;
	}
	while (cur && cur->next != target)
		cur = cur->next;
	if (cur->next == target)
	{
		temp = cur->next;
		cur->next = temp->next;
		free(temp);
	}
	return ;
}

char	*ft_strdupgnl(char *src)
{
	char	*output;
	int		i;

	i = 0;
	output = (char *)malloc((ft_strlen(src) + 1) * sizeof(char));
	while (src[i] != '\0')
	{
		output[i] = src[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}
