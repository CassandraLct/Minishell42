/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:38:27 by clecat            #+#    #+#             */
/*   Updated: 2022/11/21 12:51:57 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//2 fonctions
//affiche le pwd
void	pwd(char **c_env)
{
	int	i;

	i = 0;
	while (c_env[i])
	{
		if (strncmp(c_env[i], "PWD=", 4) == 0)
		{
			while (c_env[i])
				printf("%s\n", c_env[i] + 4);
		}
		i++;
	}
}

void	verif_arg_exit(t_min mini, int i, char **argv)
{
	char	*err;

	err = "numeric argument required";
	if (strdigit(argv[i]) == 0)
	{
		if (argv[i + 1] == NULL)
		{
			printf("exit\n");
			exit(atoi(argv[i]) % 256);
		}
		else
		{
			printf("exit\nminishell: exit : too many arguments\n");
			mini.ret_err = 1;
		}
	}
	else if (strdigit(argv[i]) == 1)
	{
		printf("exit\nminishell: exit: %s: %s\n", argv[i], err);
		exit(255);
	}
}

// exit doit avoir 0 ou 1 arg, qui doit etre numerique
//a modifier en fonction du lexer
//strcmp a faire
void	exit_min(char **argv, t_min mini)
{
	int	i;

	i = 2;
	if (strcmp(argv[1], "exit") == 0)
	{
		if (argv[i] == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		while (argv[i])
		{
			verif_arg_exit(mini, i, argv);
			break ;
		}
	}
}
