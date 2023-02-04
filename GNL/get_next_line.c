/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:22:42 by clecat            #+#    #+#             */
/*   Updated: 2023/02/03 13:09:32 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*saveaftline(char *src)
{
	char	*dest;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (src[i] != '\n' && src[i] != '\0')
		i++;
	if (src[i] == '\0')
	{
		free(src);
		return (NULL);
	}
	dest = ft_calloc3(sizeof(src), ft_strlen2(src) - i + 2);
	if (!dest)
		return (NULL);
	i++;
	while (src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	free(src);
	return (dest);
}

static char	*savebfrn(char *src)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	if (!src || src[0] == '\0')
		return (NULL);
	while (src[i] != '\n' && src[i])
		i++;
	i++;
	dest = ft_calloc3(sizeof(src), i + 1);
	if (!dest)
		return (NULL);
	j = 0;
	while (j < i)
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*save;
	char		*line;
	int			red;
	int			i;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE)
		buf[i++] = '\0';
	red = 1;
	while (ft_strchr(buf, '\n') == NULL && red > 0)
	{
		red = read(fd, buf, BUFFER_SIZE);
		if (red < 0 || (red == 0 && !save))
			return (NULL);
		buf[red] = '\0';
		save = ft_strjoin2(save, buf);
	}
	line = savebfrn(save);
	save = saveaftline(save);
	if (!save && !line)
		return (NULL);
	return (line);
}
