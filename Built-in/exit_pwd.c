/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:38:27 by clecat            #+#    #+#             */
/*   Updated: 2022/11/23 18:16:23 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//2 fonctions
//affiche le pwd (voir si modifier lors du changement)
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

/*verifie si les arguments d'exit sont valide ou non et si il y en a plus qu'un 
et renvoie le code erreur approprié(bash)*/
void	verif_arg_exit(t_min mini, int i)
{
	char	*err;

	err = "numeric argument required";
	if (strdigit(mini.tab[i]) == 0)
	{
		if (mini.tab[i + 1] == NULL)
		{
			printf("exit\n");
			exit(atoi(mini.tab[i]) % 256);
		}
		else
		{
			printf("exit\nminishell: exit: too many arguments\n");
			mini.ret_err = 1;
		}
	}
	else if (strdigit(mini.tab[i]) == 1)
	{
		printf("exit\nminishell: exit: %s: %s\n", mini.tab[i], err);
		exit(255);
	}
}

// exit doit avoir 0 ou 1 arg, qui doit etre numerique
// exit $34 : exit correctement dans le bash (voir si gerer avec le lexer et le $)
//la fonction exit de minishell soit redirige vers la verif des arguments
void	exit_min(t_min mini)
{
	int	i;

	i = 1;
	if (strcmp(mini.tab[0], "exit") == 0)
	{
		if (mini.tab[i] == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		while (mini.tab[i])
		{
			verif_arg_exit(mini, i);
			break ;
		}
	}
}
