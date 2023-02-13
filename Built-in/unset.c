/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:18 by clecat            #+#    #+#             */
/*   Updated: 2023/02/13 04:37:54 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//bash-3.2$ unset bonjour=
//bash: unset: `bonjour=': not a valid identifier
char	**unset_var(char **tab_cmd, char *str)
{
	char	**cpy;
	int		i;

	i = 0;
	cpy = malloc(sizeof(char *) * (tablen(tab_cmd) + 1));//leaks
	while (tab_cmd[i])
	{
		if (ft_strncmp(tab_cmd[i], str, ft_strlen(str)) == 0)
		{
			while (i < tablen(tab_cmd) && tab_cmd[i + 1])
			{
				cpy[i] = ft_strdup(tab_cmd[i + 1]);
				i++;
			}
			cpy[i] = NULL;
			free_tab(tab_cmd);
			tab_cmd = ft_cpytab(cpy);
			tab_cmd[i] = NULL;
			free_tab(cpy);
			return (tab_cmd);
		}
		cpy[i] = ft_strdup(tab_cmd[i]);
		i++;
	}
	return (tab_cmd);
}

// verifie si argument present ou non dans env
void	unset_verif_var(t_min *mini, int y, char **cmd)
{
	int	i;

	i = 0;
	while (mini->c_env[i])
	{
		if (ft_strncmp(mini->c_env[i], cmd[y], ft_strlen(cmd[y]))
			== 0)
		{
			mini->c_env = unset_var(mini->c_env, cmd[y]);
			break ;
		}
		i++;
	}
	i = 0;
	while (mini->c_exp[i])
	{
		if (ft_strncmp(mini->c_exp[i], cmd[y], ft_strlen(cmd[y]))
			== 0)
		{
			mini->c_exp = unset_var(mini->c_exp, cmd[y]);
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

//l'arg ne doit pas avoir de egale
void	unset(t_min *mini, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (check_var(cmd[i]) == 0)
		{
			unset_verif_var(mini, i, cmd);
			mini->ret_err = 0;
		}
		else
		{
			ft_print_error_msg3("minishell: unset: `", cmd[1],
				"': not a valid identifier\n");
			mini->ret_err = 1;
		}
		i++;
	}
}
