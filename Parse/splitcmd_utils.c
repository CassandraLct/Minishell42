/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:56:36 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/01/19 11:20:50 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_double_space(char *line)
{
	char	*resu;
	int		i;
	int		j;

	i = ft_strlen(line) + 1;
	resu = ft_calloc(i, sizeof(*resu));
	i = 0;
	j = 0;
	while (line[i])
	{
		if (!(line[i] == ' ' && line[i + 1] == ' '))
		{
			resu[j] = line[i];
			j++;
		}
		i++;
	}
	return (resu);
}

// count the commands, possible problem with the redirection without space
int	count_cmd(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				i++;
		}
		else if (line[i] == '"')
		{
			i++;
			while (line[i] != '"')
				i++;
		}
		else if (line[i] == ' ')
			count++;
		i++;
	}
	return (count + 1);
}

// count the number of redirection defined in ched c but also in cotes
// no bigdeal as the use is for malloc, bigger is not a problem
int	count_redir(char **list, char c)
{
	int	i;
	int	resu;

	i = 0;
	resu = 0;
	while (list[i])
	{
		if (list[i][0] == c)
			resu++;
		i++;
	}
	return (resu);
}

// count the number of > >> < or << even if in cotes
int	count_all_redir(char *temp)
{
	int	i;
	int	resu;

	i = 0;
	resu = 0;
	while (temp[i])
	{
		if (temp[i] == '>' && temp[i + 1] != '>')
			resu++;
		else if (temp[i] == '<' && temp[i + 1] != '>')
			resu++;
		i++;
	}
	return (resu);
}
