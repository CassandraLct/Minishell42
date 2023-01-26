/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/01/26 12:57:14 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_in(t_cmd **cmd, int nb)
{
	int		i;
	int		fd;
	int		fdglobalin;
	int		pp[2];
	char	buf[500];
	int		nb_read;

	dprintf(2, "inside ft_redir_in\n");
	if (cmd[nb]->stdin == NULL)
	{
		dprintf(2, "no redir in for cmd[%d]", nb);
		return (-2);
	}
	if (pipe(pp) == -1)
		return (-1);
//	fdglobalin = dup(pp[1]);
	fdglobalin = open("fileresu", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	i = 0;
	while (cmd[nb]->stdin[i])
	{
		if (cmd[nb]->stdin[i + 1] == NULL)
		{
			dprintf(2, "redir in without file\n");
			return (-3);
		}
		if (ft_strcmp(cmd[nb]->stdin[i], "<") == 0)
		{
			fd = open(cmd[nb]->stdin[i + 1], O_RDONLY);
			if (fd == -1)
			{
				perror(cmd[nb]->stdin[i + 1]);
				exit (66);
			}
			nb_read = 1;
			while(nb_read)
			{
				nb_read = read(fd, buf, 500);
				dprintf(2, "lecture [%s], nb_read=[%d]\n", cmd[nb]->stdin[i + 1], nb_read);
				if (nb_read)
				{
					dprintf(2, "ecriture: nb_read=[%d], buf=[%s]\n", nb_read, buf);
					write(fdglobalin, buf, nb_read);
					buf[0] = '\0';
				}
			}
			close(fd);
		}
		else if (ft_strcmp(cmd[nb]->stdin[i], "<<") == 0)
		{
			// heredoc
			// <file1<file2 wc | wc
		}
		else
			exit (66);
		i += 2;
	}
	//dup2(pp[0], 0);
	//close(pp[0]);
	close(pp[1]);
	close(fdglobalin);
	dprintf(2, "end of ft_redir_in, pp[0]=[%d]\n", pp[0]);
	return (pp[0]);
}

int	ft_redir_out(t_cmd **cmd, int nb)
{
	int	i;
	int	fd;
	int	pp[2];

//	dprintf(2, "inside ft_redir_out\n");
	i = 0;
	if (pipe(pp)  ==-1)
		exit(70);
	dup2(pp[0], 0);
	while (cmd[nb]->stdout[i])
	{
		if (cmd[nb]->stdout[i + 1] == NULL)
			exit (67);
		if (ft_strcmp(cmd[nb]->stdout[i], ">") == 0)
		{
			fd = open(cmd[nb]->stdout[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dprintf(2, "redir out simple fd=[%d], i=[%d], redir=[%s], file=[%s]\n", fd, i, cmd[nb]->stdout[i], cmd[nb]->stdout[i + 1]);
			if (fd == -1)
			{
				perror(cmd[nb]->stdout[i + 1]);
				exit (67);
			}
			dup2(fd, 1);
			close(fd);
		}
		else if (ft_strcmp(cmd[nb]->stdout[i], ">>") == 0)
		{
			fd = open(cmd[nb]->stdout[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			dprintf(2, "redir out double fd=[%d], i=[%d], redir=[%s], file=[%s]\n", fd, i, cmd[nb]->stdout[i], cmd[nb]->stdout[i + 1]);
			if (fd == -1)
			{
				perror(cmd[nb]->stdout[i + 1]);
				exit (67);
			}
			dup2(fd, 1);
			close(fd);
		}
		else
			exit (67);
		i += 2;
	}
	dup2(pp[0], 0);
	close(pp[0]);
	dprintf(2, "end of ft_redir_out, pp[1]=[%d]\n", pp[1]);
	return (pp[1]);
}

// gerer les redir out
// gerer le cas de la derniere cmd qui ne doit pas pipe
void	ft_child(t_cmd **cmd, int **pp, int i)
{
	int	fdin;
	int	fdout;

//	fdin = ft_redir_in(cmd, i);
	fdin = ft_redir_in2(cmd);
	dprintf(2, "after ft_redir_in, fdin=[%d]\n", fdin);
	if (fdin == -1)
	{
		perror("redirection in : ");
		return ;
	}
	fdout = ft_redir_out(cmd, i);
	dprintf(2, "child -> after ft_redir_out, fdout=[%d]\n", fdout);
	if (fdout == -1)
	{
		perror("redirection out :");
		return ;
	}
	if (fdin != -2)
		dup2(fdin, 0);
	else
	{
		if (i > 0)
			dup2(pp[i - 1][0], 0);
		else
		{
			// no arg en entree heredoc?
			dprintf(2, "cas sans arg de cmd qui a besoin d'arg\n");
		}
	}
	if (fdout != -2)
		dup2(fdout, 1);
	else
		dup2(pp[i][1], 1);
//	close(pp[i][0]);
//	close(pp[i][1]);
//	close(fdin);
//	close(fdout);
	dprintf(2, "pp[%d][0]=[%d], pp[%d][0]=[%d]\n", i, pp[i][0], i, pp[i][1]);
	dprintf(2, "cmd[%d][0]=[%s]\n", i, cmd[i]->cmd[0]);
	dprintf(2, "end of child\n");
	ft_set_pathexec(&g_mini, cmd[i]->cmd);
	exit (68);
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
	int	nbcmd;
	int	pid;
	int	**pp;

	dprintf(2, "max FD=[%d]\n", FOPEN_MAX);
	if (!g_mini.struct_cmd)
		exit (66);
	nbcmd = 0;
	while (g_mini.struct_cmd[nbcmd])
		nbcmd++;
	dprintf(2, "nbcmd=[%d]\n", nbcmd);
	pp = ft_test(ft_calloc(nbcmd + 1, sizeof(*pp)), NULL);
	i = 0;
	while (i < nbcmd)
	{
		pp[i] = ft_test(ft_calloc(2, sizeof(int)), NULL);
		i++;
	}
	i = 0;
	while (g_mini.struct_cmd[i])
	{
		pipe(pp[i]);
		dprintf(2, "pp[%d][0]=[%d], pp[%d][1]=[%d]\n", i, pp[i][0], i, pp[i][1]);
		pid = fork();
		if (pid == -1)
			exit (127);
		if (pid == 0)
		{
			dprintf(2, "\033[0;32m" "\nbefore child [%d]\n" "\033[0m", i);
			ft_child(g_mini.struct_cmd, pp, i);
		}
		else
			waitpid(0, NULL, 0);
		i++;
	}
	dprintf(2, "\033[0;32m" "\n\nafter last cmd i=[%d]\n" "\033[0m", i);
	return (1);
}
