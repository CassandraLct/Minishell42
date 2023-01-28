/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_dollar_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:05:30 by clecat            #+#    #+#             */
/*   Updated: 2023/01/28 16:36:44 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//4 fonctions
//supprime le dollar en dehors des cotes 
char	*rmd_bf_cotes(char *line, int savedollar)
{
	char	*tmp;
	int		i;
	int		x;

	i = 0;
	x = 0;
	tmp = malloc(sizeof(char) * ft_strlen(line));
	while (line[i])
	{
		if (i == savedollar)
			i += 1;
		tmp[x] = line[i];
		x++;
		i++;
	}
	tmp[x] = '\0';
	return (tmp);
}

//cas du dollar en dehors des cotes
int	d_outside_cotes(int i, char *line)
{
	int	savedollar;

	savedollar = i;
	while (line[i] && line[i] != '\'' && line[i] != '"')
		i++;
	if (line[i] == '\0')
		return (0);
	else
	{
		if(line[i - 1] == '$' && (line[i] == '\'' || line[i] == '"'))
			rm_dollarcotes(line, i, savedollar);
		else //if(verif_poscotes(line, i, save_dollar))
			return (0);
		return (1);
	}
}

//supprime le $ devant les cotes
char	*rm_dollarcotes(char *line, int i, int savedollar)
{
	char	*tmp;
	char	cote;
	int		j;

	cote = line[i];
	j = i + 1;
	tmp = NULL;
	while (line[j])
	{
		if (line[j] == cote)
			break ;
		j++;
	}
	if (line[j] == '\0')
		return (line);
	else
	{
		tmp = rmd_bf_cotes(line, savedollar);
		free(line);
		line = ft_strdup(tmp);
		free(tmp);
	}
	return (line);
}

//forcement un dollar present car apres fonction
int	verif_cotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' || line[i] == '\'' || line[i] == '"')
			break ;
		i++;
	}
	if (line[i] == '$')
	{
		if (d_outside_cotes(i, line) == 1)
			return (2);
		else
			return (0);
	}
	else
	{
		if (line[i] == '\'')
			return (1);
		else if (line[i] == '"')
			return (0);
	}
	return (0);
}
