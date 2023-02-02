/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_cotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:48:29 by clecat            #+#    #+#             */
/*   Updated: 2023/02/01 14:52:32 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions

//reconstruit la line en fonction
char	*join_line(char *tmp, char *s_line, char *e_line)
{
	char	*new_line;
	char	*tmp2;

	tmp2 = NULL;
	new_line = NULL;
	if (s_line != NULL && e_line == NULL)
		new_line = ft_strjoin(s_line, tmp);
	else if (s_line != NULL && e_line != NULL)
	{
		tmp2 = ft_strjoin(s_line, tmp);
		new_line = ft_strjoin(tmp2, e_line);
		free(tmp2);
	}
	else if (s_line == NULL && e_line != NULL)
		new_line = ft_strjoin(tmp, e_line);
	else
		new_line = ft_strdup(tmp);
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
		if (line[i] == cotes)
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

//modifie la line ex cas: ec'ho bonjour'/+25 lignes
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
	i = find_cotes(line);
	if (line[i] == '\0')
		return (ft_strdup(line));
	cotes = line[i];
	s_line = get_sline(line, cotes);
	e_line = get_eline(line, cotes);
	tmp = changecotesline(line, cotes);
	tmp = rm_cotes(tmp, cotes);
	// free(line);
	line = join_line(tmp, s_line, e_line);
	free(tmp);
	free_seline(s_line, e_line);
	return (line);
}

//gestion des cotes au milieu d'une commande
char	*verif_cmdcotes(char *line)
{
//	char	*tmp;
	char	*new_line;

	new_line = NULL;
//	tmp = ft_strdup(line);
//	new_line = check_line(tmp);
	new_line = check_line(line);
	free(line);
//	free(tmp);
	return (new_line);
}
