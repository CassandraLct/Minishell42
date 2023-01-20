/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:22:42 by clecat            #+#    #+#             */
/*   Updated: 2023/01/18 13:29:04 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//4 fonctions
//recupere le debut de la ligne
char	*recup_startline(char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (line[i] && line[i] != '$')
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (line[i] && line[i] != '$')
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

//recupere la fin de la ligne
char	*recup_endline(int i, char *line)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = malloc(sizeof(char) * ((ft_strlen(line) - i) + 1));
	while (line[i])
	{
		tmp[j] = line[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

//supprime les $$
void	rm_d_dollar(void)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(g_mini.line));
	while (g_mini.line[i])
	{
		if (g_mini.line[i] == '$' && g_mini.line[i + 1] == '$')
			i += 2;
		tmp[j] = g_mini.line[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	free(g_mini.line);
	g_mini.line = ft_strdup(tmp);
	free(tmp);
}

//modifie la line pour chaque dollar rencontrer
void	recup_dollarvar(int nb_dollar)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (k != nb_dollar)
	{
		tmp = malloc(sizeof(char) * (ft_strlen(g_mini.line) + 1));
		while (g_mini.line[i] != '$')
			i++;
		i += 1;
		while (g_mini.line[i] != ' ' && g_mini.line[i] != '\0')
			tmp[j++] = g_mini.line[i++];
		tmp[j] = '\0';
		j = 0;
		i = 0;
		ft_dollar(tmp);
		free(tmp);
		k++;
	}
}
