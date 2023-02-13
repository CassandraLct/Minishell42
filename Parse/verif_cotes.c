/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_cotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:48:29 by clecat            #+#    #+#             */
/*   Updated: 2023/02/13 11:42:40 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions
//reconstruit la line en fonction
char	*join_line(char *tmp, char *s_line, char *e_line)
{
	char	*new_line;

	new_line = NULL;
	if (tmp[0] != '\0')
		new_line = join_linetmp(s_line, tmp, e_line);
	else if (tmp[0] == '\0')
		new_line = join_wout_tmp(s_line, e_line);
	if (s_line)
		free(s_line);
	if (e_line)
		free(e_line);
	return (new_line);
}

//ajoute des cotes exterieures pour que la string ne soit pas split
char	*add_cotesout(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = NULL;
	if (line[0] == '\0')
		return (ft_strdup(line));
	tmp = malloc(sizeof(char) * (ft_strlen(line) + 3));
	tmp[j] = '"';
	j += 1;
	while (line[i])
	{
		tmp[j] = line[i];
		j++;
		i++;
	}
	tmp[j] = '"';
	tmp[j + 1] = '\0';
	return (tmp);
}

//supprime les cotes en plein milieu
char	*rm_cotes(char *line, char cotes)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(line) + 1);
	while (line[i])
	{
		while (line[i] == cotes && (line[i + 1] != cotes
				&& line[i - 1] != cotes))
			i += 1;
		tmp[j] = line[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	free(line);
	line = add_cotesout(tmp);
	free(tmp);
	return (line);
}

//modifie la line ex cas: ec'ho bonjour' /+25 lignes + 6variables au lieu de 5
char	*check_line(char *line)
{
	char	*tmp;
	char	*s_line;
	char	*e_line;
	char	cotes;
	int		i;

	i = 0;
	tmp = NULL;
	s_line = NULL;
	e_line = NULL;
	if (line[i] == '\0')
		return (ft_strdup(line));
	i = find_cotes(line);
	cotes = line[i];
	s_line = get_sline(line, cotes);
	e_line = get_eline(line, cotes);
	tmp = get_tmp(line, cotes);
	free(line);
	line = join_line(tmp, s_line, e_line);
	if (tmp)
		free(tmp);
	return (line);
}

//gestion des cotes au milieu d'une commande
void	verif_cmdcotes(t_min *mini)
{
	char	*new_line;
	char	*tmp_line;
	int		i;

	new_line = NULL;
	tmp_line = NULL;
	i = count_cotes(mini->line);
	if (i < 2)
		return ;
	tmp_line = remove_double_char(mini->line, '"', 1);
	free(mini->line);
	mini->line = remove_double_char(tmp_line, '\'', 1);
	free(tmp_line);
	tmp_line = ft_strdup(mini->line);
	new_line = check_line(tmp_line);
	free(mini->line);
	mini->line = ft_strdup(new_line);
	printf("mini.line = {%s}\n", mini->line);
	free(new_line);
}
