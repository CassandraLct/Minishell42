/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:56:36 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/12 10:21:15 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//5 fonctions
//remove all the multiple space to keep only one
char	*remove_double_char(char *line, char c, int remove_both_char)
{
	char	*resu;
	int		i;
	int		j;

	i = ft_strlen(line) + 1;
	resu = ft_test(ft_calloc(i, sizeof(*resu)), NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (!(line[i] == c && line[i + 1] == c))
		{
			resu[j] = line[i];
			j++;
		}
		else if (remove_both_char)
			i++;
		i++;
	}
	return (resu);
}

// count the commands
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
// only used for malloc
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

// calculate if the charactere s[i] is inside a quote (1) or not (0)
int	ft_qpar(char *s, int i)
{
	int	quoteparity;
	int	j;

	quoteparity = 0;
	j = 0;
	while (j <= i)
	{
		if (s[j] == '\'' || s[j] == '"')
			quoteparity = (quoteparity + 1) % 2;
		j++;
	}
	return (quoteparity);
}

// put space before and after < > << >> if there are missing
// cat <'<' end probleme a regler
char	*ft_space_bracket(char *s)
{
	char	*resu;
	int		i;
	int		k;

	i = 2 * count_all_redir(s) + 1;
	resu = ft_test(ft_calloc((ft_strlen(s) + i), sizeof(*resu)), NULL);
	i = 0;
	k = 0;
	while (s[i])
	{
		if (ft_qpar(s, i) == 0 && ((i != 0 && s[i] == '>' && s[i - 1] != ' '
					&& s[i - 1] != '>') || (i != 0 && s[i] == '<'
					&& s[i - 1] != ' ' && s[i - 1] != '<')))
				resu[k++] = ' ';
		resu[k++] = s[i];
		if (ft_qpar(s, i) == 0 && ((s[i + 1] && s[i] == '>' && s[i + 1] != ' '
					&& s[i + 1] != '>') || (s[i + 1] && s[i] == '<'
					&& s[i + 1] != ' ' && s[i + 1] != '<')))
				resu[k++] = ' ';
		i++;
	}
	return (resu);
}
