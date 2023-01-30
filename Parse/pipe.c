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

int	ft_redir_out(t_cmd **cmd, int nb)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (cmd[nb]->stdout[i])
	{
		if (cmd[nb]->stdout[i + 1] == NULL)
			exit (67);
		if (ft_strcmp(cmd[nb]->stdout[i], ">") == 0)
		{
			if (fd)
				close(fd);
			fd = open(cmd[nb]->stdout[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror(cmd[nb]->stdout[i + 1]);
			}
		}
		else if (ft_strcmp(cmd[nb]->stdout[i], ">>") == 0)
		{
			if (fd)
				close(fd);
			fd = open(cmd[nb]->stdout[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror(cmd[nb]->stdout[i + 1]);
			}
		}
		else
			exit (67);
		i += 2;
	}
	dprintf(2, "end of ft_redir_out, fd=[%d]\n", fd);
	return (fd);
}

// gerer les redir out
void	ft_child(t_cmd **cmd, int **pp, int i)
{
	int		fdin;
	int		fdout;

	if (i == 0)
		fdin = ft_redir_in2(cmd);
	else
	{
		fdin = pp[i - 1][0];
	}
	if (fdin)
	{
		dprintf(2, "child[%d] => i=0, dup2(fdin, 0), fdin=[%d]\n", i, fdin);
		dup2(fdin, 0);
	}
	if (i != 0)
	{
		close(pp[i - 1][0]);
		close(pp[i - 1][1]);
	}
	fdout = pp[i][1];
	dup2(fdout, 1);
	close(pp[i][0]);
	close(pp[i][1]);
	ft_set_pathexec(&g_mini, cmd[i]->cmd);
	exit (68);
}

void	ft_parent(t_cmd **cmd, int **pp, int i)
{
	int		fdin;
	pid_t	pid;

	if (i == 0)
		fdin = ft_redir_in2(cmd);
	else
		fdin = pp[i - 1][0];
	if (fdin)
	{
		dprintf(2, "parent => i=0, dup2(fdin, 0), fdin=[%d]\n", fdin);
		dup2(fdin, 0);
	}
	if (i != 0)
	{
		close(pp[i - 1][0]);
		close(pp[i - 1][1]);
	}
	dprintf(2, "parent => pp[%d][0]=[%d], pp[%d][1]=[%d] / ", i, pp[i][0], i, pp[i][1]);
	dprintf(2, "parent => cmd[%d][0]=[%s] / end of parent\n", i, cmd[i]->cmd[0]);
	pid = fork();
	if (pid == 0)
		ft_set_pathexec(&g_mini, cmd[i]->cmd);
	return ;
}

// wqit for all the childs to finish
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
		ft_execve(mini, all_path, pathcmd, cmd);
		free_tab(all_path);
		free_tab(pathcmd);
	}
}

void	ft_set_pathexec2(t_min *mini, char **cmd)
{
	char	**all_path;
	char	**pathcmd;

	pathcmd = NULL;
	pathcmd = init_cmd(cmd, pathcmd);
	all_path = recup_path(mini);
	if (all_path == NULL)
	{
		mini->ret_err = 127;
		printf("minishell: %s: No such file or directory\n", cmd[0]);
		free_tab(pathcmd);
		return ;
	}
	ft_exec2(mini, all_path, pathcmd, cmd);
}

// exec the child process in the while
void	ft_child(t_cmd **cmd, int **pp, int i)
{
	int		fdin;
//	int		fdout;

	if (i == 0)
		fdin = ft_redir_in(cmd);
	else
		fdin = pp[i - 1][0];
	dup2(fdin, 0);
	if (fdin)
		close(fdin);
//	fdout = ft_redir_out(cmd, i);
//	dprintf(2, "fdout=[%d]", fdout);
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
