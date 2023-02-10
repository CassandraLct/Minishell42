/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:37:12 by clecat            #+#    #+#             */
/*   Updated: 2023/02/10 16:55:49 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

//4 fonctions
//verifie si que des n pour l'option
int	check_arg_opt(char *arg)
{
	int	i;
	int	y;

	i = 1;
	y = 1;
	while (arg[i])
	{
		if (arg[i] == 'n')
			y++;
		i++;
	}
	if (y != i)
		return (1);
	return (0);
}

//print les args option valide
int	print_arg_opt(char **arg, int i)
{
	if (arg[i + 1] == NULL)
		return (0);
	else if (arg[i + 1] != NULL)
	{
		if (check_arg_opt(arg[i + 1]) == 0)
			i += 2;
		else
			i += 1;
		while (arg[i] != NULL)
		{
			if (check_arg_opt(arg[i]) == 0)
				i += 1;
			if (arg[i + 1] == NULL)
				printf("%s", arg[i]);
			else
				printf("%s ", arg[i]);
			i++;
		}
	}
	return (1);
}

//verifie l'option
int	check_opt(char **arg)
{
	int	i;

	i = 1;
	if (check_arg_opt(arg[i]) == 0)
	{
		print_arg_opt(arg, i);
		return (0);
	}
	else if (check_arg_opt(arg[i]) == 1)
	{
		while (arg[i])
		{
			if (arg[i + 1] == NULL)
				printf("%s\n", arg[i]);
			else
				printf("%s ", arg[i]);
			i++;
		}
	}
	return (0);
}

//verifie si echo a des arguments ou non
void	echo(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (cmd[1] == NULL || cmd[1][0] == '\0')
		printf("\n");
	else if (cmd[i][0] == '-')
		check_opt(cmd);
	else
	{
		while (cmd[i] && cmd[i][0] != '\0' && (cmd[i][j] >= 32
			&& cmd[i][j] <= 126))
		{
			if (cmd[i + 1] == NULL)
				printf("%s\n", cmd[i]);
			else
				printf("%s ", cmd[i]);
			i++;
		}
	}
	g_mini.ret_err = 0;
	return ;
}
