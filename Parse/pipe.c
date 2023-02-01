/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/01 12:09:47 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//+25lignes
int	ft_redir_in(t_cmd **cmd, int nb)
{
	int	i;
	int	fd;
	int	pp[2];

	printf("inside ft_redir_in\n");
	i = 0;
	if (pipe(pp) == -1)
		return (-1);
	if (cmd[nb]->stdin == NULL)
		return (-2);
	while (cmd[nb]->stdin[i])
	{
		if (cmd[nb]->stdin[i + 1] == NULL)
			return (-3);
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
			// heredoc(cmd[nb]);
		}
		else
			exit (66);
		i += 2;
	}
	close(pp[1]);
	printf("end of ft_redir_in, pp[0]=[%d]\n", pp[0]);
	return (pp[0]);
}

//+25 lignes
int	ft_redir_out(t_cmd **cmd, int nb)
{
	int	i;
	int	fd;
	int	pp[2];

	printf("inside ft_redir_out\n");
	i = 0;
	pipe(pp);
	while (cmd[nb]->stdout[i])
	{
		if (cmd[nb]->stdout[i + 1] == NULL)
			exit (67);
		if (ft_strcmp(cmd[nb]->stdout[i], ">") == 0)
		{
			fd = open(cmd[nb]->stdout[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644); //line too long
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
			fd = open(cmd[nb]->stdout[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644); //line too long
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
	printf("end of ft_redir_out, pp[1]=[%d]\n", pp[1]);
	return (pp[1]);
}

// gerer les redir out / +25 lignes
// gerer le cas de la derniere cmd qui ne doit pas pipe
void	ft_child(t_cmd **cmd, int **pp, int i)
{
	int	fdin;
	int	fdout;

	fdin = ft_redir_in(cmd, i);
	printf("after ft_redir_in, fdin=[%d]\n", fdin);
	if (fdin == -1)
	{
		perror("redirection in : ");
		return ;
	}
	fdout = ft_redir_out(cmd, i);
	printf("child -> after ft_redir_out, fdout=[%d]\n", fdout);
	if (fdout == -1)
	{
		perror("redirection out :");
		return ;
	}
	dup2(fdin, 0);
	dup2(pp[i][1], 1);
	close(pp[i][0]);
	close(pp[i][1]);
	close(fdin);
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

// +25 lignes
int	piping(void)
{
	int	i;
	int	nbcmd;
	int	pid;
	int	**pp;

	printf("max FD=[%d]\n", FOPEN_MAX);
	if (!g_mini.struct_cmd)
		exit (66);
	nbcmd = 0;
	while (g_mini.struct_cmd[nbcmd])
		nbcmd++;
	printf("nbcmd=[%d]\n", nbcmd);
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
		printf("pp[%d][0]=[%d], pp[%d][1]=[%d]\n", i, pp[i][0], i, pp[i][1]);
		pid = fork();
		if (pid == -1)
			exit (127);
		if (pid == 0)
		{
			printf("\033[0;32m" "\nbefore child [%d]\n" "\033[0m", i);
			ft_child(g_mini.struct_cmd, pp, i);
		}
		else
			waitpid(0, NULL, 0);
		i++;
	}
	dprintf(2, "\033[0;32m" "\n\nafter last cmd i=[%d]\n" "\033[0m", i);
	return (1);
}
