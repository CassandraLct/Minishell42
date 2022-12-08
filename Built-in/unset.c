/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:18 by clecat            #+#    #+#             */
/*   Updated: 2022/12/08 13:44:04 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//bash-3.2$ unset bonjour=
//bash: unset: `bonjour=': not a valid identifier
//pb malloc : des que strncmp
char	**unset_var_env(t_min mini)
{
	char	**cpy;
	int		i;

	i = 0;
	cpy = malloc(sizeof(char *) * (tablen(mini.c_env)));
	while (mini.c_env[i])
	{
		if (strncmp(mini.c_env[i], mini.tab[1], ft_strlen(mini.tab[1])) == 0)
		{
			while (i < tablen(mini.c_env) && mini.c_env[i + 1])
			{
				cpy[i] = ft_strdup(mini.c_env[i + 1]);
				i++;
			}
			cpy[i] = NULL;
			free_tab(mini.c_env);
			mini.c_env = ft_cpytab(cpy);
			free_tab(cpy);
			return (mini.c_env);
		}
		cpy[i] = ft_strdup(mini.c_env[i]);
		i++;
	}
	return (mini.c_env);
}

// verifie si argument present ou non dans env
t_min	unset_verif_var(t_min mini)
{
	int	i;

	i = 0;
	while (mini.c_env[i])
	{
		if (strncmp(mini.c_env[i], mini.tab[1], ft_strlen(mini.tab[1])) == 0)
		{
			mini.c_env = unset_var_env(mini);
			return (mini);
		}
		i++;
	}
	return (mini);
}

//verifie si = present ou non et si premier caract est un chiffre
int	check_var(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[0] >= '0' && str[0] <= '9')
		return (1);
	while (str[i])
	{
		if (str[i] == '=')
			j++;
		i++;
	}
	if (j != 0)
		return (1);
	return (0);
}

// l'arg ne doit pas avoir de egale
t_min	unset(t_min mini)
{
	int	i;

	i = 1;
	while (mini.tab[i])
	{
		if (check_var(mini.tab[i]) == 0)
			mini = unset_verif_var(mini); //return quelque chose
		else
		{
			printf("minishell: unset: `%s':", mini.tab[1]);
			printf(" not a valid identifier\n");
			mini.ret_err = 1;
		}
		i++;
	}
	return (mini);
}
