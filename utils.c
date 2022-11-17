/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:12:41 by clecat            #+#    #+#             */
/*   Updated: 2022/11/17 14:42:08 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	size_t			j;
	unsigned char	*s3;
	unsigned char	*s4;

	s3 = (unsigned char *)s1;
	s4 = (unsigned char *)s2;
	i = 0;
	j = 1;
	if (n == 0)
		return (-1);
	while (s3[i] && s4[i] && s3[i] == s4[i] && j < n)
	{	
		i++;
		j++;
	}
	return (s3[i] - s4[i]);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

//verifie que la string est que des digit
int	strdigit(char *str)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (str[y])
	{
		if (str[y] >= '0' && str[y] <= '9')
			i++;
		y++;
	}
	if (i != y)
		return (1);
	return (0);
}

char	*ft_strdup(char *s)
{
	char	*dest;
	int		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	dest = malloc(sizeof(char) * i + 1);
	if (dest == 0)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
