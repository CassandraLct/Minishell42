/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/25 16:50:24 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <string.h>

//5 fonctions
/*export (qqc) sans égale s'affiche que dans export
si = afficher aussi dans env
si var deja dans env et que la valeur est modifier, elle reste dans env mais
la val est bien changer*/

//copy sur la derniere ligne d'env;
char	**add_valenv(t_min mini, char *str)
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
	mini.c_env = ft_cpytab(cpy);
	return (mini.c_env);
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

//verifier si = present et quelque chose apres le =
void	new_vars(t_min mini)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (mini.tab[i])
	{
		while (mini.tab[i][j] != '\0')
		{
			if (ft_isdigit(mini.tab[1][0]) == 1)
			{
				printf("minishell: `%s': not a valid identifier\n", mini.tab[i]);
				exit(1);
			}
			if (mini.tab[i][j] == '=')
			{
				if (mini.tab[i][j + 1] == '\0')
					printf("cas 1: a copier que dans export: '%s'\n", mini.tab[i]);
				else
				{
					printf("copie dans env et export\n");
					mini.c_env = add_valenv(mini, mini.tab[i]);
					return ;
				}
			}
			j++;
		}
		i++;
		j = 0;
	}
	printf("cas 3: a copie que dans export : '%s'\n", mini.tab[1]);
}

//add new_var ou affiche export
void	export(t_min mini)
{
	mini.c_exp = init_exp(mini.c_env);
	if (mini.tab[1] != NULL)
		new_vars(mini);
	print_export(mini.c_exp);
}
