/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:38 by clecat            #+#    #+#             */
/*   Updated: 2023/02/12 15:26:49 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//#include <stdlib.h>
//#include <string.h>

//4 fonctions

//verifie si index envoyer est deja present dans copy exp
//cmp = env ou cpy
int	check_exp(char **cmp, char **c_exp, int index)
{
	int	i;

	i = 0;
	if (!c_exp)
		return (0);
	while (c_exp[i])
	{
		if (ft_strcmp(cmp[index], c_exp[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

//trie export par ordre ascii
//cmp = c_env ou cpy
char	**order_exp(char **c_exp, char **cmp)
{
	int	index;
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (tablen(cmp) > y)
	{
		index = 0;
		while (check_exp(cmp, c_exp, index) != 0)
			index++;
		while (cmp[i])
		{
			if (ft_strcmp(cmp[index], cmp[i]) > 0
				&& check_exp(cmp, c_exp, i) == 0)
				index = i;
			i++;
		}
		c_exp = fill_exp(c_exp, cmp[index]);
		i = 0;
		y++;
	}
	return (c_exp);
}

int	is_valid_export_identifier(char *str)
{
	if (str == NULL)
		return (0);
	if (str[0] == '\0')
		return (0);
	if (ft_strchr(str, '-'))
		return (0);
	return (1);
}

void	do_export(t_min *mini, char **cmd, int i)
{
	while (cmd[i] != NULL)
	{
		if (cmd[i][0] == '\0')
		{
			printf("minishell: %s: `': not a valid identifier\n", cmd[0]);
			g_mini.ret_err = 1;
		}
		if (verif_space(cmd[i]) == 1
			|| is_valid_export_identifier(cmd[i]) == 0)
		{
			printf("minishell: %s: `%s': not a valid identifier\n",
				cmd[0], cmd[i]);
			g_mini.ret_err = 1;
		}
		else
			new_vars(mini, cmd[i], i, cmd);
		i++;
	}
}

//add new_var ou affiche export
void	export(t_min *mini, char **cmd)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
	{
		print_export(mini->c_exp);
	}
	else
	{
		do_export(mini, cmd, i);
	}
}
