/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/01/23 10:50:24 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_in(t_cmd **cmd, int nb)
{
	int	i;
	int	fd;
	int	pp[2];

	i = 0;
	pipe(pp);
	while (cmd[nb]->stdin[i])
	{
		if (cmd[nb]->stdin[i + 1] == NULL)
			exit (66);
		if (ft_strcmp(cmd[nb]->stdin[i], "<") == 0)
		{
			fd = open(cmd[nb]->stdin[i + 1], O_RDONLY);
			if (fd == -1)
			{
				perror(cmd[nb]->stdin[i + 1]);
				exit (66);
			}	
			dup2(fd, 0);
			dup2(pp[1], 1);
			close(fd);
			}
		else if (ft_strcmp(cmd[nb]->stdin[i], "<<") == 0)
		{
			// heredoc
		}
		else
			exit (66);
		i += 2;
	}
	close(pp[1]);
	return (pp[0]);
}

int	ft_redir_out(t_cmd **cmd, int nb)
{
	int	i;
	int	fd;
	int	pp[2];

	i = 0;
	pipe(pp);
	while (cmd[nb]->stdout[i])
	{
		if (cmd[nb]->stdout[i + 1] == NULL)
			exit (67);
		if (ft_strcmp(cmd[nb]->stdout[i], ">") == 0)
		{
			fd = open(cmd[nb]->stdout[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
			{
				perror(cmd[nb]->stdout[i + 1]);
				exit (67);
			}
			dup2(fd, 1);
			dup2(pp[0], 0);
			close(fd);
		}
		else if (ft_strcmp(cmd[nb]->stdout[i], ">>") == 0)
		{
			fd = open(cmd[nb]->stdout[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644); // parametrer pour >>
			if (fd == -1)
			{
				perror(cmd[nb]->stdout[i + 1]);
				exit (67);
			}
			dup2(fd, 1);
			dup2(pp[0], 0);
			close(fd);
		}
		else
			exit (67);
		i += 2;
	}
	close(pp[0]);
	return (pp[1]);
}

void	ft_child(int *pp)
{
	int	fdin;

	fdin = open(pp->filein, O_RDONLY);
	if (pp->fdin == -1)
	{
		perror(pp->filein);
		return ;
	}
	pp->cmdpath[0] = ft_findcmdpath(pp->path, pp->cmdarg[0][0]);
	dup2(pp->fdin, 0);
	dup2(pp->pip[1], 1);
	close(pp->pip[0]);
	close(pp->pip[1]);
	close(pp->fdin);
	if (pp->cmdpath[0] != NULL)
	{
		if (execve(pp->cmdpath[0], pp->cmdarg[0], envp) == -1)
			ft_freeallexit(pp, 127);
	}
	ft_freeallexit(pp, 127);
}

/*
void	ft_pipe(t_cmd **cmd, int i, int fdin, int fdout)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit(127);
	if (pid == 0)
		ft_child();
	return (1);
}
*/

int	piping(void)
{
	int	i;
//	int	ppin;
//	int	ppout;
	int	pid;
	int	pp[2];

	i = 0;
	if (!g_mini.struct_cmd)
		exit (66);
	while (g_mini.struct_cmd[i])
	{
		if (!g_mini.struct_cmd[i + 1])
		{
			// last pipe or single command
		}
		else
		{
			//ppin = ft_redir_in(g_mini.struct_cmd, i);
			//ppout = ft_redir_out(g_mini.struct_cmd, i);
			//ft_pipe(g_mini.struct_cmd, i, ppin, ppout);
			pipe(pp);
			pid = fork();
			if (pid == -1)
				exit (127);
			if (pid == 0)
				ft_child(pp);
		}
	}
	// ft_parent; ?
	return (1);
}
