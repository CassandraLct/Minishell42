/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/04 15:54:32 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_return_redir_in(t_cmd **cmd, int last_redir, int fd)
{
	if (last_redir == 0)
		return (0);
	else if (last_redir == 1)
	{
		if (fd)
			close(fd);
		fd = open(ft_last_single_redir_in(cmd), O_RDONLY);
		return (fd);
	}
	else if (last_redir == 2)
		return (fd);
	return (0);
}

//
int	heredoc_launcher(t_cmd **cmd, int i, int j, int *fd)
{
	if (ft_strcmp(cmd[i]->stdin[j], "<<") == 0)
	{
		if (cmd[i]->stdin[j + 1] == NULL)
		{
			printf(ERR_HEREDOC);
			g_mini.ret_err = 258;
			return (1);
		}
		else
		{
			if (*fd)
				close(*fd);
			*fd = heredoc(cmd[i]->stdin[j + 1]);
		}
	}
	return (0);
}

// return the fd of the redir in
int	ft_redir_in(t_cmd **cmd)
{
	int		last_redir;
	int		fd;
	int		i;
	int		j;
	int		nbh;

	last_redir = ft_what_is_last_redir_in(cmd);
	fd = 0;
	i = 0;
	nbh = ft_nb_heredoc(cmd);
	while (nbh > 0 && cmd[i] && g_mini.sig_heredoc != 0)
	{
		j = 0;
		while (cmd[i]->stdin && cmd[i]->stdin[j] && g_mini.sig_heredoc != 0)
		{
			if (heredoc_launcher(cmd, i, j, &fd) == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (fd_return_redir_in(cmd, last_redir, fd));
}

// open file and return the fd
// close fd if allready open, open the file how=1 for > and how=2 for >>
int	ft_open_file(char *file, int fd, int how)
{
	if (fd)
		close(fd);
	if (how == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(file);
		g_mini.ret_err = 1;
	}
	return (fd);
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
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			g_mini.ret_err = 258;
			exit (g_mini.ret_err);
		}
		if (ft_strcmp(cmd[nb]->stdout[i], ">") == 0)
			fd = ft_open_file(cmd[nb]->stdout[i + 1], fd, 1);
		else if (ft_strcmp(cmd[nb]->stdout[i], ">>") == 0)
			fd = ft_open_file(cmd[nb]->stdout[i + 1], fd, 2);
		else
		{
			dprintf(2, "unexpected error\n"); //minishell: syntax error near unexpected token `>'
			g_mini.ret_err = 258;
			exit (g_mini.ret_err);
		}
		i += 2;
	}
	return (fd);
}
