/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annexe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:36:11 by clecat            #+#    #+#             */
/*   Updated: 2023/02/10 13:47:34 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//verifie si la var PWD est vide (cd)
char	*verif_pwd(char *line)
{
	char	*tmp;

	if (ft_strcmp(line, "PWD=") == 0)
		tmp = ft_strjoin(line, "/");
	else
		tmp = ft_strdup(line);
	return (tmp);
}

//verifie si espace dans nom de variable(export)
int	verif_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
	{
		if (str[i] == 32)
			return (1);
		i++;
	}
	return (0);
}

//recup le nom de la variable(export_change_val)
char	*get_namevar(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	while (str[i] && str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	verif_cmdcotesempty(char *line)
{
	if (ft_strncmp(line, "export \"\"", ft_strlen("export \"\"")) == 0
		|| ft_strncmp(line, "export \'\'", ft_strlen("export \'\'")) == 0)
		return (1);
	else if (ft_strncmp(line, "unset \"\"", ft_strlen("unset \"\"")) == 0
		|| ft_strncmp(line, "unset \'\'", ft_strlen("unset \'\'")) == 0)
	{
		printf("minishell: unset: `': not a valid identifier\n");
		g_mini.ret_err = 1;
		return (1);
	}
	else if (ft_strncmp(line, "cd \"\"", ft_strlen("cd \"\"")) == 0
		|| ft_strncmp(line, "cd \'\'", ft_strlen("cd \'\'")) == 0)
		return (1);
	return (0);
}

//modifie line et tmp
char	*get_tmp(char *line, char cotes)
{
	char	*tmp;
	char	*tmp2;

	tmp = changecotesline(line, cotes);
	printf("tmpchangeline= %s\n", tmp);
	tmp2 = ft_strdup(tmp);
	free(tmp);
	tmp = rm_cotes(tmp2, cotes);
	return (tmp);
}
