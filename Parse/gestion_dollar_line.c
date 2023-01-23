/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_dollar_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:31:40 by clecat            #+#    #+#             */
/*   Updated: 2023/01/23 15:15:46 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//3 fonctions

char	*recup_val(char *str)
{
	char	*tmp;
	char	*val;
	int	i;

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
	val = ft_strdup(g_mini.c_env[i]);
	return (val);
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
	free(name_var);
	while (tmp[i] != '=')
		i++;
	i += 1;
	name_var = malloc(sizeof(char) * (i + 1));
	while (tmp[i] && tmp[i] != '\0')
	{
		name_var[j] = tmp[i];
		i++;
		j++;
	}
	name_var[j] = '\0';
	return (name_var);
}

//change la line en fonction de name_var
char	*change_line(char *name_var, char *line)
{
	char	*tmp;
	char	*tmp2;
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	while (line[i] && line[i] != '$')
		i++;
	if (i == 0)
	{
		tmp = NULL;
		new_line = ft_strdup(name_var);
		i += 1;
	}
	else
	{
		new_line = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(name_var) - i));
		tmp = malloc(sizeof(char) * (i + 1));
		i = 0;
		while (line[i] && line[i] != '$')
		{
			tmp[i] = line[i];
			i++;
		}
		tmp[i] = '\0';
		i += 1;
		new_line = ft_strjoin(tmp, name_var);
		free(tmp);
	}
	while (line[i] && line[i] != '\0' && line[i] != '$' && line[i] != 32)
		i++;
	if (line[i] != '\0')
	{
		tmp = malloc(sizeof(char) * (ft_strlen(line) - i));
		tmp2 = ft_strdup(new_line);
		free(new_line);
		j = 0;
		while (line[i])
		{
			tmp[j] = line[i];
			j++;
			i++;
		}
		tmp[j] = '\0';
		new_line = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
	}
	return (new_line);
}
