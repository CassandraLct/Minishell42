/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/01/30 12:58:16 by rdi-marz         ###   ########.fr       */
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
//		return ;
		exit(1);
	}
	else
	{
//		mini->pid = fork();
//		if (mini->pid == -1)
//		{
//			perror("Fork failed");
//			exit(EXIT_FAILURE);
//		}
//		else if (mini->pid == 0)
			ft_execve(mini, all_path, pathcmd, cmd);
//		else
//			waitpid(mini->pid, &mini->ret_err, 0);
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
	int		fdout;

	if (i == 0)
		fdin = ft_redir_in(cmd);
	else
		fdin = pp[i - 1][0];
	dup2(fdin, 0);
	close(fdin);
	fdout = ft_redir_out(cmd, i);
	dprintf(2, "fdout=[%d]", fdout);
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

// main function to manage pipes
int	piping(void)
{
	int		i;
	int		nbcmd;
	pid_t	pid;
	int		**pp;
	int		fdin;

	if (!g_mini.struct_cmd)
		exit (66);
	nbcmd = 0;
	while (g_mini.struct_cmd[nbcmd])
		nbcmd++;
	pp = ft_test(ft_calloc(nbcmd + 1, sizeof(*pp)), NULL);
	i = 0;
	while (i < nbcmd)
	{
		pp[i] = ft_test(ft_calloc(2, sizeof(int)), NULL);
		i++;
	}
	i = 0;
	while (g_mini.struct_cmd[i + 1])
	{	
		if (pipe(pp[i]) == -1)
			dprintf(2, "pipe bug\n");
		pid = fork();
		if (pid == -1)
			exit (127);
		if (pid == 0)
		{
			//ft_child(g_mini.struct_cmd, pp, i);
			if (i == 0)
				fdin = ft_redir_in(g_mini.struct_cmd);
			else
				fdin = pp[i - 1][0];
			dup2(pp[i][1], 1);
			dup2(fdin, 0);
			if (fdin)
				close(fdin);
			close(pp[i][1]);
			close(pp[i][0]);
			ft_set_pathexec2(&g_mini, g_mini.struct_cmd[i]->cmd);
		}
		else
			ft_parent(pp, i);
		i++;
	}
	ft_last_command(g_mini.struct_cmd, pp, i);
	ft_wait_all();
	return (1);
}

// cat | cat | ls
// <file1 cat | cat | cat | cat


// not in use
int	piping_expanded(void)
{
	int		i;
	int		nbcmd;
	pid_t	pid;
	int		**pp;
	int		fdin;

	fdin = 0;
	if (!g_mini.struct_cmd)
		exit (66);
	nbcmd = 0;
	while (g_mini.struct_cmd[nbcmd])
		nbcmd++;
	pp = ft_test(ft_calloc(nbcmd + 1, sizeof(*pp)), NULL);
	i = 0;
	while (i < nbcmd)
	{
		pp[i] = ft_test(ft_calloc(2, sizeof(int)), NULL);
		i++;
	}
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
		{
			close(pp[i][1]);
			if (fdin)
				close(fdin);
			if (i > 0)
				close(pp[i - 1][0]);
		}
		i++;
	}
	//ft_parent(g_mini.struct_cmd, pp, i);
	pid = fork();
	if (pid == 0)
	{
		dup2(pp[i - 1][0], 0);
		//dup out if needed
		ft_set_pathexec2(&g_mini, g_mini.struct_cmd[i]->cmd);
	}
	if (i > 0)
		close(pp[i - 1][0]);
	else if (fdin)
		close(fdin);
	ft_wait_all();
	return (1);
}
