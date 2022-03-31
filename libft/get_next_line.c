/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:07:59 by tratanat          #+#    #+#             */
/*   Updated: 2022/03/05 01:06:36 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*get_next_line(int fd)
{
	char				*buffer;
	int					bytesread;
	char				*output;
	int					newline;
	static t_storedlst	*readlst = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	output = NULL;
	newline = getstored(&readlst, &output, fd);
	while (!newline)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread <= 0)
			break ;
		newline = checknl(&output, buffer, fd, &readlst);
	}
	if (output && newline)
		output = ft_strnjoin(output, "\n", 1);
	free(buffer);
	if (!output || !ft_strlen(output))
		return (NULL);
	return (output);
}

int	checknl(char **output, char *buffer, int fd, t_storedlst **readlst)
{
	int	i;

	i = 0;
	if (!(*buffer))
		return (0);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	*output = ft_strnjoin(*output, buffer, i);
	if (buffer[i] == '\n')
	{
		if (!storeline(ft_strdupgnl(buffer + i + 1), fd, readlst))
			return (-1);
		return (1);
	}
	else
		return (0);
}

int	storeline(char *buffer, int fd, t_storedlst **readlst)
{
	t_storedlst	*temp;

	temp = *readlst;
	while (temp && temp->fd != fd)
		temp = temp->next;
	if (temp == NULL)
	{
		temp = (t_storedlst *)malloc(sizeof(t_storedlst));
		if (!temp)
			return (0);
		temp->fd = fd;
		temp->stored = buffer;
		temp->next = *readlst;
		*readlst = temp;
	}
	else if (temp->fd == fd)
		temp->stored = buffer;
	if (!(*buffer))
	{
		ft_lstdel(readlst, temp);
		free(buffer);
	}
	return (1);
}

int	getstored(t_storedlst **readlst, char **output, int fd)
{
	t_storedlst	*temp;
	char		*tempstr;
	int			newline;

	temp = *readlst;
	while (temp && temp->fd != fd)
		temp = temp->next;
	if (temp && temp->fd == fd)
	{
		if (temp->stored)
		{
			tempstr = temp->stored;
			newline = checknl(output, temp->stored, fd, readlst);
			free(tempstr);
			if (!newline)
				ft_lstdel(readlst, temp);
			return (newline);
		}
	}
	return (0);
}
