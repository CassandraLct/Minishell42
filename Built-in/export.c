/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:38 by clecat            #+#    #+#             */
/*   Updated: 2022/12/08 17:19:18 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <string.h>

//5 fonctions
/*si var deja dans env et que la valeur est modifier, elle reste dans env mais
la val est bien changer*/

//verifier si valeur deja presente et changer que sa valeur
int	verif_modif_var(char **str, char *cmp)
{
	char	*name_var;
	int		i;

	i = 0;
	name_var = malloc(sizeof(char) * (ft_strlen(cmp) + 1));
	name_var = recup_name(cmp, name_var);
	while (str[i])
	{
		if (strncmp(str[i], name_var, ft_strlen(name_var)) == 0)
			return (1);
		i++;
	}
	free(name_var);
	return (0);
}

//redirige vers l'ajout ou la modification
//+25lignes (35 lignes)
t_min	new_vars(t_min mini, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (verif_modif_var(mini.c_env, str) == 1 && verif_modif_var(mini.c_exp, str) == 1)//a mettre dans une autre fonction
	{
		printf("variable deja presente dans env et exp, valeur a modifier\n");
		j += 1;
	}
	else if (verif_modif_var(mini.c_exp, str) == 1 && verif_modif_var(mini.c_env, str) == 0)
	{
		printf("variable presente dans exp valeur a modifier et ajout dans env\n");
		j += 1;
	}
	while (str[i])
	{
		if (ft_isdigit(str[0]) == 1)
		{
			printf("minishell: `%s': not a valid identifier\n", mini.tab[i]);
			exit(1);
		}
		if (str[i] == '=' && str[i + 1] != '\0' && j == 0)
		{
			mini.c_env = add_valenv(mini, str);
			mini.c_exp = add_valexp(mini, str);
			j += 1;
		}
		i++;
	}
	if (j == 0)
		mini.c_exp = add_valexp(mini, str);
	return (mini);
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
		if (strcmp(cmp[index], c_exp[i]) == 0)
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
			if (strcmp(cmp[index], cmp[i]) > 0
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
t_min	export(t_min mini)
{
	int	i;

	i = 1;
	if (mini.tab[1] == NULL)
		print_export(mini.c_exp);
	else
	{
		while (mini.tab[i] != NULL)
		{
			mini = new_vars(mini, mini.tab[i]);
			i++;
		}
	}
	return (mini);
}
