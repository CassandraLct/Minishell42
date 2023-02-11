/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:28:10 by clecat            #+#    #+#             */
/*   Updated: 2023/02/11 16:42:17 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//4 fonctions
//get indice endcotes
int	get_endcotes(char *line, char cotes, int j)
{
	while (line[j] && line[j] != cotes)
		j++;
	while ((line[j] && line[j] != '\0' && line[j] != ' ' && line[j] != '<'
			&& line[j] != '>'))
		j++;
	return (j);
}

// check if tmp is only cotes
void	verif_tmp(char *line)
{
	if (line[0] == '\'' && line[1] == '\'')
		line[0] = '\0';
	else if (line[0] == '"' && line[1] == '"')
		line[0] = '\0';
	return ;
}

//join line when tmp is not empty
char	*join_linetmp(char *s_line, char *tmp, char *e_line)
{
	char	*n_line;
	char	*tmp2;

	tmp2 = NULL;
	n_line = NULL;
	if (s_line != NULL && e_line == NULL)
		n_line = ft_strjoin(s_line, tmp);
	else if (s_line != NULL && e_line != NULL)
	{
		tmp2 = ft_strjoin(s_line, tmp);
		n_line = ft_strjoin(tmp2, e_line);
		free(tmp2);
	}
	else if (s_line == NULL && e_line != NULL)
		n_line = ft_strjoin(tmp, e_line);
	else if (s_line == NULL && e_line == NULL)
		n_line = ft_strdup(tmp);
	return (n_line);
}

//join line when tmp empty
char	*join_wout_tmp(char *s_line, char *e_line)
{
	char	*n_line;

	n_line = NULL;
	if (s_line != NULL && e_line != NULL)
		n_line = ft_strjoin(s_line, e_line);
	else if (s_line != NULL && e_line == NULL)
		n_line = ft_strdup(s_line);
	else if (s_line == NULL && e_line != NULL)
		n_line = ft_strdup(e_line);
	else if (s_line == NULL && e_line == NULL)
		n_line = ft_strdup("");
	return (n_line);
}

int	count_cotes(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
			j += 1;
		i++;
	}
	return (j);
}
