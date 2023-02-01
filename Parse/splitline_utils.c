/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitline_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/01 10:54:16 by clecat           ###   ########.fr       */
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
	if (g_mini.line[0] == '|' && g_mini.line[0] != '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		exit (1);
	}
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
