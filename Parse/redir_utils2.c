/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/12 16:10:55 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exit if the redirection has no arg to open
void	ft_exit_when_no_arg(void)
{
	write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
	g_mini.ret_err = 258;
	exit (g_mini.ret_err);
}

// exit if the redirection has no arg to open
void	ft_exit_unexpected_token(t_cmd **cmd, int nb, int i)
{
	ft_print_error_msg3(ERR_TOKEN_SHORT, &(cmd[nb]->stdout[i][0]), "'\n");
	g_mini.ret_err = 258;
	exit (g_mini.ret_err);
}

// return the fd of the redirection out
int	ft_redir_out(t_cmd **cmd, int nb)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (cmd[nb]->stdout[i])
	{
		if (cmd[nb]->stdout[i + 1] == NULL)
			ft_exit_when_no_arg();
		if (ft_strcmp(cmd[nb]->stdout[i], ">") == 0)
			fd = ft_open_file(cmd[nb]->stdout[i + 1], fd, 1);
		else if (ft_strcmp(cmd[nb]->stdout[i], ">>") == 0)
			fd = ft_open_file(cmd[nb]->stdout[i + 1], fd, 2);
		else
			ft_exit_unexpected_token(cmd, nb, i);
		i += 2;
	}
	return (fd);
}

// return type of the last redir: 0 is none, 1 is <, 2 is <<
int	ft_what_is_last_redir_in(t_cmd **cmd)
{
	int	i;
	int	j;
	int	resu;

	i = 0;
	resu = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i]->stdin[j])
		{
			if (ft_strcmp(cmd[i]->stdin[j], "<") == 0)
				resu = 1;
			else if (ft_strcmp(cmd[i]->stdin[j], "<<") == 0)
				resu = 2;
			j++;
		}
		i++;
	}
	return (resu);
}
