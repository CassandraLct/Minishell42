/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/10 17:07:32 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//5 fonctions
// exec the child process in the while
void	ft_child(t_cmd **cmd, int **pp, int i)
{
	int		fdin;
	int		fdout;

	if (i == 0)
		fdin = ft_redir_in(cmd);
	else
		fdin = pp[i - 1][0];
	dup2(fdin, 0);
	if (fdin)
		close(fdin);
	fdout = ft_redir_out(cmd, i);
	if (fdout)
	{
		dup2(fdout, 1);
		close(fdout);
	}
	else
		dup2(pp[i][1], 1);
	close(pp[i][0]);
	close(pp[i][1]);
	redirection2(&g_mini, cmd[i]);
	exit (0);
}

// exec the parent process in the while
void	ft_parent(int **pp, int i)
{
	close(pp[i][1]);
	if (i > 0)
		close(pp[i - 1][0]);
	return ;
}

void	last_command_child(t_cmd **cmd, int **pp, int i)
{
	int	fdin;
	int	fdout;

	if (i == 0)
		fdin = ft_redir_in(cmd);
	else
		fdin = pp[i - 1][0];
	dup2(fdin, 0);
	fdout = ft_redir_out(cmd, i);
	if (fdout)
	{
		dup2(fdout, 1);
		close(fdout);
	}
	if (i > 0)
		close(pp[i - 1][0]);
	redirection2(&g_mini, cmd[i]);
	exit (g_mini.ret_err);
}

// exec the last command or the only cmd if no pipe
void	ft_last_command(t_cmd **cmd, int **pp, int i)
{
	pid_t	pid;
	int		fdin;
	int		status;

	pid = fork();
	g_mini.pid = pid;
	fdin = 0;
	if (pid == 0)
		last_command_child(cmd, pp, i);
	if (i > 0)
		close(pp[i - 1][0]);
	else if (fdin)
		close(fdin);
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("Minishell:");
		exit(EXIT_FAILURE);
	}
	g_mini.ret_err = (status / 256) % 256;
	return ;
}

// wait for all the childs to finish
void	ft_wait_all(void)
{
	pid_t	wpid;
	int		status;

	wpid = wait(&status);
	while (wpid > 0)
	{
		wpid = wait(&status);
	}
}
