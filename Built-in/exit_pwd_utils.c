/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pwd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:38:27 by clecat            #+#    #+#             */
/*   Updated: 2023/02/09 14:43:06 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//exit in case the digit is too big
void	exit_number_too_big(t_min *mini, int i, char **cmd)
{
	printf("exit\nminishell: %s: %s: %s\n", cmd[0], cmd[i], ERR_NUM);
	mini->ret_err = 255;
	exit(mini->ret_err);
}

//exit in case only one valid digit
void	exit_valid_number(t_min *mini, int i, char **cmd)
{
	if (g_mini.nb_cmd == 1)
		printf("exit\n");
	mini->ret_err = ft_atoi(cmd[i]) % 256;
	exit(mini->ret_err);
}

/*verifie si les arguments d'exit sont valide ou non et si il y en a plus qu'un 
et renvoie le code erreur approprié(bash)*/
void	verif_arg_exit(t_min *mini, int i, char **cmd)
{
	if (strdigit(cmd[i]) == 0)
	{
		if (ft_strlen(cmd[i]) >= 19)
			exit_number_too_big(mini, i, cmd);
		if (cmd[i + 1] == NULL)
			exit_valid_number(mini, i, cmd);
		else
		{
			printf("exit\nminishell: exit: too many arguments\n");
			mini->ret_err = 1;
		}
	}
	else if (strdigit(cmd[i]) == 1)
	{
		printf("exit\nminishell: exit: %s: %s\n", cmd[i], ERR_NUM);
		mini->ret_err = 255;
		exit(mini->ret_err);
	}
}
