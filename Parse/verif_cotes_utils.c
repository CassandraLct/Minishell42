/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_cotes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:54:56 by clecat            #+#    #+#             */
/*   Updated: 2023/02/09 11:29:12 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 3fonctions
// +25 lignes cut a partir d'ici
char	*get_sline(char *line, char cotes)
{
	char	*s_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s_line = NULL;
	while (line[i] && line[i] != cotes)
		i++;
	while (line[i] && line[i] != ' ' && i != 0 && line[i] != '<'
		&& line[i] != '>')
		i--;
	j = ft_strlen(line) - i;
	if (i != 0)
	{
		s_line = malloc(sizeof(char) * ((ft_strlen(line) - j) + 1));
		j = 0;
		while (line[j] && j <= i)
		{
			s_line[j] = line[j];
			j++;
		}
		s_line[j] = '\0';
	}
	return (s_line);
}

char	*cpy_eline(char *line, int j)
{
	char	*e_line;
	int		i;

	e_line = malloc(sizeof(char) * ((ft_strlen(line) - j) + 1));
	i = 0;
	while (line[j] != '\0')
	{
		e_line[i] = line[j];
		i++;
		j++;
	}
	e_line[i] = '\0';
	return (e_line);
}

// too many functions +25 lignes
char	*get_eline(char *line, char cotes)
{
	char	*e_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	e_line = NULL;
	while (line[i] && line[i] != cotes)
		i++;
	j = i + 1;
	while (line[i] && line[i] != ' ' && i != 0 && line[i] != '<'
		&& line[i] != '>')
		i--;
	while (line[j] && line[j] != cotes)
		j++;
	while (line[j] && line[j] != ' ' && line[j] != '<' && line[j] != '>'
		&& line[j] != '\0')
		j++;
	if (line[j] != '\0')
		e_line = cpy_eline(line, j);
	return (e_line);
}

//recupere la partie de la line
char	*tmpline(char *line, int start, int end)
{
	char	*tmp;
	int		i;

	tmp = malloc(sizeof(char) * ((end - start) + 1));
	i = 0;
	while (line[start] && start != end)
	{
		tmp[i] = line[start];
		i++;
		start++;
	}
	tmp[i] = '\0';
	return (tmp);
}

//copier la partie de la line avec les cotes
char	*changecotesline(char *line, char cotes)
{
	char	*tmp;
	int		start;
	int		end;
	int		i;
	int		j;

	i = 0;
	while (line[i] && line[i] != cotes)
		i++;
	j = i + 1;
	while (line[i] && line[i] != ' ' && i != 0 && line[i] != '<'
		&& line[i] != '>')
		i--;
	start = i;
	end = get_endcotes(line, cotes, j);
	i = 0;
	if (line[start] == ' ' || line[start] == '<' || line[start] == '>')
		start += 1;
	tmp = tmpline(line, start, end);
	verif_tmp(tmp);
	return (tmp);
}
