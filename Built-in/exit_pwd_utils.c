/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pwd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:38:27 by clecat            #+#    #+#             */
/*   Updated: 2023/02/12 09:26:22 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//3 fonctions
//exit in case the digit is too big
void	exit_number_too_big(t_min *mini, int i, char **cmd)
{
	write(2, "exit\nminishell: ", 16);
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": ", 2);
	write(2, cmd[i], ft_strlen(cmd[i]));
	write(2, ": ", 2);
	write(2, ERR_NUM, ft_strlen(ERR_NUM));
	write(2, "\n", 1);
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

//exit in case the argument is not a number
void	exit_not_numeric(t_min *mini, int i, char **cmd)
{
	write(2, "exit\nminishell: exit: ", 22);
	write(2, cmd[i], ft_strlen(cmd[i]));
	write(2, ": ", 2);
	write(2, ERR_NUM, ft_strlen(ERR_NUM));
	write(2, "\n", 1);
	mini->ret_err = 255;
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
			write(2, "exit\nminishell: exit: too many arguments\n", 41);
			mini->ret_err = 1;
		}
	}
	else if (strdigit(cmd[i]) == 1)
		exit_not_numeric(mini, i, cmd);
}
