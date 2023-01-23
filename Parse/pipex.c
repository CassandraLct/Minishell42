/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/01/23 10:50:21 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child(t_pipe *pp, char **envp)
{
	pp->fdin = open(pp->filein, O_RDONLY);
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

void	ft_parent(t_pipe *pp, char **envp)
{
	waitpid(0, NULL, 0);
	pp->fdout = open(pp->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pp->fdout == -1)
	{
		perror(pp->fileout);
		ft_freeallexit(pp, 1);
	}
	pp->cmdpath[1] = ft_findcmdpath(pp->path, pp->cmdarg[1][0]);
	dup2(pp->fdout, 1);
	dup2(pp->pip[0], 0);
	close(pp->pip[0]);
	close(pp->fdout);
	close(pp->pip[1]);
	if (pp->cmdpath[1] != NULL)
	{
		if (execve(pp->cmdpath[1], pp->cmdarg[1], envp) == -1)
			exit(127);
	}
	ft_freeallexit(pp, 127);
}

int	pipex(int argc, char **argv, char **envp)
{
	t_pipe	*pp;

	pp = ft_init(argc, argv, envp);
	pipe(pp->pip);
	pp->pin = fork();
	if (pp->pin == -1)
		exit(127);
	if (pp->pin == 0)
		ft_child(pp, envp);
	else
		ft_parent(pp, envp);
	return (1);
}
