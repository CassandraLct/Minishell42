/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:38 by clecat            #+#    #+#             */
/*   Updated: 2023/02/10 17:02:19 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <string.h>

//5 fonctions

//verifier si valeur deja presente
int	verif_modif_var(char **str, char *cmp)
{
	char	*name_var;
	char	*new_str;
	int		i;

	i = 0;
	name_var = recup_name(cmp);
	while (str[i])
	{
		new_str = ft_strjoin(str[i], "=");
		if (ft_strncmp(new_str, name_var, ft_strlen(name_var)) == 0)
		{
			free(name_var);
			return (1);
		}
		i++;
	}
	free(name_var);
	free(new_str);
	return (0);
}

//redirige vers l'ajout ou la modification
void	new_vars(t_min *mini, char *str, int y, char **cmd)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) == 1 || str[0] == '=')
	{
		printf("minishell: export:`%s': not a valid identifier\n", cmd[y]);
		mini->ret_err = 1;
		return ;
	}
	redir_changeval(mini, str);
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1] != '\0' && mini->nb_passage_exp == 0)
		{
			add_valenv(mini, str);
			add_valexp(mini, str);
			mini->nb_passage_exp += 1;
		}
		i++;
	}
	if (mini->nb_passage_exp == 0)
		add_valexp(mini, str);
	mini->nb_passage_exp = 0;
	mini->ret_err = 0;
}

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

//add new_var ou affiche export
void	export(t_min *mini, char **cmd)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
		print_export(mini->c_exp);
	else
	{
		while (cmd[i] != NULL)
		{
			if (cmd[i][0] == '\0')
			{
				printf("minishell: %s: `': not a valid identifier\n", cmd[0]);
				g_mini.ret_err = 1;
			}
			else if (verif_space(cmd[i]) == 1)
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
}
