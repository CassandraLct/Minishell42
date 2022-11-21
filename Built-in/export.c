/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/21 17:32:20 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <string.h>

//5 fonctions
/*export (qqc) sans égale s'affcihe que dans export
si = afficher aussi dans env*/

//copy sur la derniere ligne d'env;
void	add_valenv(t_min mini, char *str)
{
	int		i;
	char	**cpy;

	i = 0;
	while (mini.c_env[i])
		i++;
	cpy = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (mini.c_env[i])
	{
		cpy[i] = ft_strdup(mini.c_env[i]);
		i++;
	}
	cpy[i] = ft_strdup(str);
	cpy[i + 1] = NULL;
	//free_tab(mini.c_env);
	mini.c_env = ft_cpytab(cpy);
}

//voir pour modifier check_exp
void	add_valexp(t_min mini, char *str)
{
	char	**cpy;
	int		i;

	i = 0;
	while (mini.c_exp[i])
		i++;
	cpy = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (mini.c_exp[i])
	{
		cpy[i] = ft_strdup(mini.c_exp[i]);
		i++;
	}
	cpy[i] = ft_strdup(str);
	cpy[i + 1] = NULL;
	free_tab(mini.c_env);
	return ;
}

//verifier si = present et quelque chose apres le =
void	new_vars(t_min mini, char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (ft_isdigit(arg[0]) == 1)
		{
			printf("`%s': not a valid identifier\n", arg);
			exit(1);
		}
		if (arg[i] == '=')
		{
			if (arg[i + 1] == '\0') //a modifier (voir si gerer avec le lexer)
				printf("cas 1: a copier que dans export: '%s'\n", arg);
			else
			{
				printf("copie dans env et export\n");
				add_valenv(mini, arg);
				return ;
			}
		}
		i++;
	}
	printf("cas 3: a copie que dans export : '%s'\n", arg);
}

//trie export par ordre ascii
void	order_exp(t_min mini)
{
	int	index;
	int	i;

	i = 0;
	while (tablen(mini) != 0)
	{
		index = 0;
		while (check_exp(mini, index) != 0)
			index++;
		while (mini.c_env[i])
		{
			if (strcmp(mini.c_env[index], mini.c_env[i]) > 0
				&& check_exp(mini, i) == 0)
				index = i;
			i++;
		}
		fill_exp(mini, mini.c_env[index]);
		i = 0;
	}
}

//add new_var ou affiche export
void	export(t_min mini)
{
	char	*arg;

	arg = "bonjour=a+b";
	mini.c_exp = init_exp(mini.c_env);
	if (arg != NULL)
		new_vars(mini, arg);
	else
		print_export(mini);
}
