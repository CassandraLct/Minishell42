/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:18 by clecat            #+#    #+#             */
/*   Updated: 2023/01/09 09:08:05 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//bash-3.2$ unset bonjour=
//bash: unset: `bonjour=': not a valid identifier
char	**unset_var(char **tab, char *str)
{
	char	**cpy;
	int		i;

	i = 0;
	cpy = malloc(sizeof(char *) * (tablen(tab)));
	while (tab[i])
	{
		if (ft_strncmp(tab[i], str, ft_strlen(str)) == 0)
		{
			while (i < tablen(tab) && tab[i + 1])
			{
				cpy[i] = ft_strdup(tab[i + 1]);
				i++;
			}
			cpy[i] = NULL;
			free_tab(tab);
			tab = ft_cpytab(cpy);
			tab[i] = NULL;
			free_tab(cpy);
			return (tab);
		}
		cpy[i] = ft_strdup(tab[i]);
		i++;
	}
	return (tab);
}

// verifie si argument present ou non dans env
void	unset_verif_var(t_min *mini, int y)
{
	int	i;

	i = 0;
	while (mini->c_env[i])
	{
		if (ft_strncmp(mini->c_env[i], mini->tab[y], ft_strlen(mini->tab[y]))
			== 0)
		{
			mini->c_env = unset_var(mini->c_env, mini->tab[y]);
			break ;
		}
		i++;
	}
	i = 0;
	while (mini->c_exp[i])
	{
		if (ft_strncmp(mini->c_exp[i], mini->tab[y], ft_strlen(mini->tab[y]))
			== 0)
		{
			mini->c_exp = unset_var(mini->c_exp, mini->tab[y]);
			break ;
		}
		i++;
	}
}

//verifie si = present ou non et si premier caract est un chiffre
int	check_var(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (str[0] >= '0' && str[0] <= '9')
		return (2);
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
void	unset(t_min *mini)
{
	int	i;

	i = 1;
	while (mini->tab[i])
	{
		if (check_var(mini->tab[i]) == 0)
			unset_verif_var(mini, i);
		else
		{
			printf("minishell: unset: `%s':", mini->tab[1]);
			printf(" not a valid identifier\n");
			mini->ret_err = 1;
		}
		i++;
	}
}
