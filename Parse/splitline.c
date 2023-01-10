/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:20:02 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/01/10 17:55:28 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// return 0 if the '(39) or the "(34) are mixed or not by even number
int	iscotevalid(char *line)
{
	int	i;
	int	simplecote;
	int	doublecote;

	i = 0;
	simplecote = 0;
	doublecote = 0;
	while(line[i])
	{
		if (line[i] == '\'')
			simplecote = (simplecote + 1) % 2;
		else if (line[i] == '"')
			doublecote = (doublecote + 1) % 2;
		if (simplecote == 1 && doublecote == 1)
			return (0);	
		i++;
	}
	if (simplecote == 1 || doublecote == 1)
		return (0);
	return (1);
}

int	count_instruct(char *line)
{
	int	i;
	int	nbinst;

	i = 0;
	nbinst = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;	
			while(line[i] && line[i] != '\'')
			   i++;	
		}
		else if (line[i] == '"')
		{
			i++;
			while(line[i] && line[i] != '"')
				i++;
		}
		else if (line[i] == '|' && line[i + 1] != '|')
			nbinst++;
		i++;
	}
	return (nbinst + 1);
}

cahr	*getinst(char *line, int j)
{

}


char	**spliter(t_min mini)
{
	char	**result;
	int		i;
	int		j;
	int		instlen;

	result = NULL;
	if (iscotevalid(mini.line) == 0)
	{
		// gestion erreur
		printf("command not valid\n");
		return (NULL);
	}
	i = count_instruct(mini.line);
	result = malloc((i + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	j = 0;
	while(j < i)
	{
		result[j] = getinst(mini.line, j);
		j++;
	}
	return (result);
}











