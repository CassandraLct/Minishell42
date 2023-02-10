/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_dollar_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:31:40 by clecat            #+#    #+#             */
/*   Updated: 2023/02/10 09:57:36 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions
//recupere la ligne de la var correspondante
char	*recup_val(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin(str, "=");
	while (g_mini.c_env[i])
	{
		if (ft_strncmp(g_mini.c_env[i], tmp, ft_strlen(tmp)) == 0)
		{
			break ;
		}
		i++;
	}
	free(str);
	free(tmp);
	return (g_mini.c_env[i]);
}

//recupere la valeur de la variable a partir du egale
char	*recup_valvar(char *name_var)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = recup_val(name_var);
	while (tmp[i] != '=')
		i++;
	i += 1;
	name_var = malloc(sizeof(char) * (ft_strlen(tmp + i) + 1));
	while (tmp[i] && tmp[i] != '\0')
	{
		name_var[j] = tmp[i];
		i++;
		j++;
	}
	name_var[j] = '\0';
	return (name_var);
}

//recupere le debut de la ligne
char	*startline(char *line, int i, char	*n_var)
{
	char	*tmp;
	char	*new_line;

	tmp = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (line[i] && line[i] != '$')
	{
		tmp[i] = line[i];
		i++;
	}
	tmp[i] = '\0';
	i += 1;
	new_line = ft_strjoin(tmp, n_var);
	free(tmp);
	return (new_line);
}

//recupere la fin de la ligne
char	*endline(char *line, int i, char *n_line)
{
	char	*tmp;
	char	*tmp2;
	char	*new_line;
	int		j;

	tmp = malloc(sizeof(char) * (ft_strlen(line) - i));
	tmp2 = ft_strdup(n_line);
	free(n_line);
	j = 0;
	while (line[i])
		tmp[j++] = line[i++];
	tmp[j] = '\0';
	new_line = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	return (new_line);
}

//change la line en fonction de name_var
char	*change_line(char *n_var, char *line)
{
	char	*n_line;
	char	*new_line;
	int		i;

	i = 0;
	new_line = NULL;
	while (line[i] && line[i] != '$')
		i++;
	if (i == 0)
		n_line = ft_strdup(n_var);
	else
		n_line = startline(line, i, n_var);
	i += 1;
	while (line[i] && line[i] != '\0' && line[i] != '$' && line[i] != 32
		&& line[i] != '\'' && line[i] != '"' && line[i] != '/')
		i++;
	if (line[i] != '\0')
	{
		new_line = endline(line, i, n_line);
		free(n_var);
		return (new_line);
	}
	free(n_var);
	return (n_line);
}
