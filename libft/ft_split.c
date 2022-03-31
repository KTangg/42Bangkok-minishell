/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:53:17 by tratanat          #+#    #+#             */
/*   Updated: 2022/02/15 19:53:17 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		getwordcount(char const *s, char c);
int		arrword(char *str, char c, char **out, int count);

char	**ft_split(char const *s, char c)
{
	int		wordcount;
	char	**out;
	int		i;
	char	*cur;
	int		add;

	wordcount = getwordcount(s, c);
	out = (char **)malloc((wordcount + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	out[wordcount] = NULL;
	i = 0;
	cur = (char *)s;
	while (i < wordcount)
	{
		while (*cur == c && *cur)
			cur++;
		add = arrword(cur, c, out, i);
		if (!add)
			return (NULL);
		cur = cur + add;
		i++;
	}
	return (out);
}

int	arrword(char *str, char c, char **out, int count)
{
	int		len;
	int		i;

	len = 0;
	while (str[len] != c && str[len])
		len++;
	i = 0;
	*(out + count) = (char *)malloc((len + 1) * sizeof(char));
	while (i < len)
	{
		out[count][i] = str[i];
		i++;
	}
	out[count][i] = '\0';
	return (len);
}

int	getwordcount(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (!(*s))
			break ;
		while (*s != c && *s)
			s++;
		if (*s == c)
			count++;
		else if (*s == '\0')
		{
			count++;
			break ;
		}
	}
	return (count);
}
