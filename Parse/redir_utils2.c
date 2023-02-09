/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/09 11:11:30 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exit if the redirection has no arg to open
void	ft_exit_when_no_arg(void)
{
	printf("minishell: syntax error near unexpected token `newline'\n");
	g_mini.ret_err = 258;
	exit (g_mini.ret_err);
}

// exit if the redirection has no arg to open
void	ft_exit_unexpected_token(t_cmd **cmd, int nb, int i)
{
	printf("%s%s'\n", ERR_TOKEN_SHORT, cmd[nb]->stdout[i]);
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