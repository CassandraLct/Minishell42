/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/01/30 16:17:00 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//test chaque path puis execute la cmd si existante
void	ft_exec2(t_min *mini, char **all_path, char **pathcmd, char **cmd)
{
	if (verif_cmd(all_path, pathcmd, cmd) != 0)
	{
		dprintf(2, "wrong command\n");
		free_tab(all_path);
		free_tab(pathcmd);
		exit(1);
	}
	else
	{
		dprintf(2, "child[%d] => no arg given to the command\n", i);
	}
	if (i != 0)
	{
		close(pp[i - 1][0]);
		close(pp[i - 1][1]);
	}
}

void	ft_set_pathexec2(t_min *mini, char **cmd)
{
	int		fdin;
	int		fdout;

//	waitpid(0, NULL, 0);
	if (i == 0)
		fdin = ft_redir_in2(cmd);
	else
	{
		fdin = pp[i - 1][0];
	}
	if (fdin)
	{
		dprintf(2, "parent => i=0, dup2(fdin, 0), fdin=[%d]\n", fdin);
		dup2(fdin, 0);
		close(fdin);
	}
	else
	{
		dprintf(2, "parent => no arg given to the command\n");
	}

	fdout = 1; // for testing
	dprintf(2, "parent => after ft_redir_out, fdout=[%d]\n", fdout);
	if (fdout == -1)
	{
		perror("redirection out :");
		return ;
	}
<<<<<<< HEAD
	ft_exec2(mini, all_path, pathcmd, cmd);
=======
	dup2(fdout, 1);
	if (i != 0)

	{
		close(pp[i - 1][0]);
		close(pp[i - 1][1]);
	}
	close(pp[i][0]);
	close(pp[i][1]);
	dprintf(2, "parent => pp[%d][0]=[%d], pp[%d][1]=[%d] / ", i, pp[i][0], i, pp[i][1]);
	dprintf(2, "parent => cmd[%d][0]=[%s] / end of parent\n", i, cmd[i]->cmd[0]);
//	pid = fork();
//	if (pid == 0)
	ft_set_pathexec(&g_mini, cmd[i]->cmd);
	exit (68);
}

// main function to manage pipes
int	piping(void)
{
	int	i;
	int	nbcmd;
	int	pid;
	int	**pp;

	pp = ft_create_pipe(g_mini.struct_cmd);
	i = 0;
	while (g_mini.struct_cmd[i + 1])
	{	
		if (pipe(pp[i]) == -1)
			dprintf(2, "pipe bug\n");
		pid = fork();
		if (pid == -1)
			exit (127);
		if (pid == 0)
			ft_child(g_mini.struct_cmd, pp, i);
		else
			ft_parent(pp, i);
		i++;
	}
	ft_last_command(g_mini.struct_cmd, pp, i);
	ft_wait_all();
	return (1);
}
