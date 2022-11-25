/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:18 by clecat            #+#    #+#             */
/*   Updated: 2022/11/25 16:49:48 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//bash-3.2$ unset bonjour=
//bash: unset: `bonjour=': not a valid identifier
// a tester une fois la valeur remonter
char	**unset_var_env(t_min mini)
{
	char	**cpy;
	int		i;

	i = 0;
	while (mini.c_env[i])
	{
		if (strcmp(mini.c_env[i], mini.tab[1]) == 0)
			free(mini.c_env[i]);
		i++;
	}
	cpy = malloc(sizeof(char *) * (i));
	i = 0;
	while (mini.c_env[i])
	{
		cpy[i] = ft_strdup(mini.c_env[i]);
		i++;
	}
	mini.c_env = ft_cpytab(cpy);
	return (mini.c_env);
}

// verifie si argument present ou non
void	unset_verif_var(t_min mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mini.c_env[i])
	{
		if (strncmp(mini.c_env[i], mini.tab[1], ft_strlen(mini.tab[1])) == 0)
		{
			printf("free line\n");
			//unset_var_env(mini);
			j += 1;
		}
		i++;
	}
	if (j == 0)
		return ;
}

//verifie si = present ou non
int	check_var(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
void	unset(t_min mini)
{
	int	i;

	i = 1;
	while (mini.tab[i])
	{
		if (check_var(mini.tab[i]) == 0)
			unset_verif_var(mini);
		else
		{
			printf("minishell: unset: `%s': not a valid identifier\n", mini.tab[1]);
			mini.ret_err = 1;
		}
		i++;
	}
}
