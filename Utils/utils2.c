/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:12:41 by clecat            #+#    #+#             */
/*   Updated: 2023/01/09 09:11:53 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//2 fonctions
int	ft_strcmp(char *s1, char *s2)
{
	int				l1;
	int				l2;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if (l1 == l2)
		return (ft_strncmp(s1, s2, l1));
	else
		return (l1 - l2);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '	' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	result = 0;
	while (ft_isdigit(str[i]) == 1)
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}
