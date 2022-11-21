/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:18 by clecat            #+#    #+#             */
/*   Updated: 2022/11/21 17:37:27 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//bash-3.2$ unset bonjour=
//bash: unset: `bonjour=': not a valid identifier

void	unset_var_env(t_min mini, char *arg)
{
	int	i;

	i = 0;
	while (mini.c_env[i])
	{
		if (strncmp(mini.c_env[i], arg, ft_strlen(arg)) == 0)
		{
			printf("free line\n");
			free(mini.c_env[i]);
		}
		else
		{
			printf("arg n'est pas dans env\n");
			exit(0);
		}
		i++;
	}
}

void	unset(t_min mini)
{
	char	*arg;
	int		i;

	arg = "bonjour";
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			printf("minishell: unset: `%s': not a valid identifier\n", arg);
			mini.ret_err = 1;
		}
		i++;
	}
	if (arg[i] != '=')
		unset_var_env(mini, arg);
}
