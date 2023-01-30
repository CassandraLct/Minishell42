/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/01/30 17:08:38 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
//	dprintf(2, "fdout=[%d]", fdout);
	if (fdout)
	{
		dup2(fdout, 1);
		close(fdout);
	}
	else
		dup2(pp[i][1], 1);
	close(pp[i][0]);
	close(pp[i][1]);
	ft_set_pathexec2(&g_mini, cmd[i]->cmd);
	exit (68);
}

// exec the parent process in the while
void	ft_parent(int **pp, int i)
{
	close(pp[i][1]);
	if (i > 0)
		close(pp[i - 1][0]);
	return ;
}

// exec the last command or the only cmd if no pipe
void	ft_last_command(t_cmd **cmd, int **pp, int i)
{
	pid_t	pid;
	int		fdin;

	pid = fork();
	if (pid == 0)
	{
		if (i == 0)
			fdin = ft_redir_in(cmd);
		else
			fdin = pp[i - 1][0];
		dup2(fdin, 0);
		//dup out if needed
		ft_set_pathexec2(&g_mini, cmd[i]->cmd);
	}
	if (i > 0)
		close(pp[i - 1][0]);
	else if (fdin)
		close(fdin);
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

int	**ft_create_pipe(t_cmd **cmd)
{
	int	nbcmd;
	int	**pp;
	int	i;

	nbcmd = 0;
	while (cmd[nbcmd])
		nbcmd++;
	pp = ft_test(ft_calloc(nbcmd + 1, sizeof(*pp)), NULL);
	i = 0;
	while (i < nbcmd)
	{
		pp[i] = ft_test(ft_calloc(2, sizeof(int)), NULL);
		i++;
	}
	return (pp);
}
