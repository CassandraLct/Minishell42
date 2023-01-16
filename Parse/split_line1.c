/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:15:41 by clecat            #+#    #+#             */
/*   Updated: 2023/01/16 13:16:21 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//fonction essaie
char	**gestion_cotes(t_min mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mini.line[i])
	{
		while (mini.line[i] != 32)
		{
			mini.tab[j][i] = mini.line[i];
		}
		i++;
	}
	return (mini.tab);
}

//+25lignes
char	**split_line(t_min mini)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (mini.line[i])
	{
		if (mini.line[i] == 34 || mini.line[i] == 39)
		{
			while (mini.line[i++] != 34 || mini.line[i++] != 39)
			{
				j++;
				break ;
			}
		}
		i++;
	}
	if (j == 0)
		mini.tab = ft_split(mini.line, ' ');
	else
	{
		printf("ne pas split entre les cotes,redirection vers autre fonction\n");
		mini.tab = gestion_cotes(mini);
	}
	return (mini.tab);
}