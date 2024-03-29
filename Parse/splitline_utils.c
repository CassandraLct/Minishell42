/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitline_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/12 16:20:18 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//4 fonctions
// return 0 if the '(39) or the "(34) are mixed or not by even number
int	iscotevalid(char *line)
{
	int	i;
	int	simplecote;
	int	doublecote;

	i = 0;
	simplecote = 0;
	doublecote = 0;
	while (line[i])
	{
		if (line[i] == '\'' && doublecote == 0)
			simplecote = (simplecote + 1) % 2;
		else if (line[i] == '"' && simplecote == 0)
			doublecote = (doublecote + 1) % 2;
		i++;
	}
	if (simplecote == 1 || doublecote == 1)
		return (0);
	return (1);
}

// count how many instructions are between the real pipes
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
			while (line[i] && line[i] != '\'')
				i++;
		}
		else if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
		}
		else if (line[i] == '|' && line[i + 1] != '|')
			nbinst++;
		i++;
	}
	return (nbinst + 1);
}

// test if a the variable is different from error
// used to test if the malloc are ok
void	*ft_test(void *var, void *error)
{
	if (var == error)
	{
		perror(NULL);
		exit(1);
	}
	return (var);
}

// return one if the char j is a real pipe
// a real pipe is a pipe that is not inside a cote
int	is_single_pipe(int j)
{
	int	i;
	int	cote;

	i = 0;
	cote = 0;
	while (i < j)
	{
		if (g_mini.line[i] == '\'' || g_mini.line[i] == '"')
				cote = (cote + 1) % 2;
		i++;
	}
	if (j == 0)
		return (0);
	if (cote != 1 && g_mini.line[j] == '|' && g_mini.line[j + 1] != '|'
		&& g_mini.line[j - 1] != '|')
		return (1);
	return (0);
}
