/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:22:38 by clecat            #+#    #+#             */
/*   Updated: 2023/02/03 13:09:10 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen2(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin2(char *str, char *buf)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	if (!str)
	{
		str = malloc(sizeof(char) * 1);
		str[0] = '\0';
	}
	if (!str || !buf)
		return (NULL);
	tmp = malloc(sizeof(char) * ((ft_strlen2(str) + ft_strlen2(buf)) + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	if (str)
		while (str[++i] != '\0')
			tmp[i] = str[i];
	j = 0;
	while (buf[j] != '\0')
		tmp[i++] = buf[j++];
	tmp[ft_strlen2(str) + ft_strlen2(buf)] = '\0';
	free(str);
	return (tmp);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c == '\0')
		return ((char *)s + ft_strlen2(s));
	while (s[i] != '\0')
	{
		if (s[i] == (const char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

void	*ft_calloc3(size_t count, size_t size)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < (count * size))
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
