/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_dollar_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:30:01 by clecat            #+#    #+#             */
/*   Updated: 2023/01/23 16:16:43 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions 
//verifie quel cas present 
int	verif_dollarcase(char *line)
{
	char	*name_var;
	int		i;

	i = 0;
	while (line[i] && line[i] != '$')
		i++;
	if (line[i + 1] == '?')
		return (1);
	else
	{
		name_var = recup_namevar(line);
		if (verif_var(name_var) == 0)
		{
			free(name_var);
			return (2);
		}
		else
		{
			free(name_var);
			return (3);
		}
	}
	return (0);
}

//verifie si variable existante
int	verif_var(char *name_var)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin(name_var, "=");
	while (g_mini.c_env[i])
	{
		if (ft_strncmp(g_mini.c_env[i], tmp, ft_strlen(tmp)) == 0)
			break ;
		i++;
	}
	free(tmp);
	if (i == tablen(g_mini.c_env))
		return (1);
	return (0);
}

//recupere le nom de la variable (forcement un dollar)
char	*recup_namevar(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '$')
		i++;
	j = i;
	while (line[i] != '\0' && line[i] != '$' && line[i] != ' ')
	{
		i++;
	}
	tmp = malloc(sizeof(char) * (i - j + 1));
	i = j + 1;
	j = 0;
	while (line[i] != '\0' && line[i] != '$' && line[i] != ' ')
	{
		tmp[j] = line[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

//supprime le double dollar
char	*rm_d_dollar(char *tmp)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * ft_strlen(tmp));
	while (tmp[i])
	{
		if (tmp[i] == '$' && tmp[i + 1] == '$')
			i += 2;
		new_line[j] = tmp[i];
		j++;
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}

//compte le nombre de dollar
int	count_nbdollar(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '$')
			count += 1;
		i++;
	}
	return (count);
}
