/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:21:09 by clecat            #+#    #+#             */
/*   Updated: 2022/11/24 13:18:58 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//a finir (ne gere pas encore les cotes)
//+25 lignes
char	**split_line(t_min mini)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (mini.line[i])
	{
		if (mini.line[i] == 34 || mini.line[i] == 39)
		{
			c = mini.line[i];
			while (mini.line[i] != 34 || mini.line[i] != 39)
			{
				if (mini.line[i] != 34 && mini.line[i] != 39 
					&& mini.line[i + 1] == '\0')
					printf("minishell: `%s': cote not closed\n", mini.line);
				if (mini.line[i] == c)
				{
					printf("c= %c, line[i] = %c\n", c, mini.line[i]);
					printf("a copier dans le tableau, %s\n", mini.line);
				}
				j++;
				i++;
			}
		}
		i++;
	}
	if (j == 0)
		mini.tab = ft_split(mini.line, ' ');
	return (mini.tab);
}

/*void	verif_line(t_min mini)
{
	char	**builtin;
	int		i;
	int		j;

	while(mini.tab[i])
	{
		i++;
	}
}*/
