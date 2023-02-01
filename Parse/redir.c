/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/01/30 15:40:38 by rdi-marz         ###   ########.fr       */
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

// return the fd of the redir in
int	ft_redir_in(t_cmd **cmd)
{
	int		last_redir;
	int		fd;
	int		i;
	int		j;

	last_redir = ft_what_is_last_redir_in(cmd);
	fd = 0;
	if (ft_nb_heredoc(cmd) != 0)
	{
		i = 0;
		while (cmd[i])
		{
			j = 0;
			while (cmd[i]->stdin && cmd[i]->stdin[j])
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
						if (fd)
							close(fd);
						fd = heredoc(cmd[i]->stdin[j + 1]);
					}
				}
				j++;
			}
			i++;
		}
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
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//		dprintf(2, "in open, fd=[%d]\n", fd);
	}
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(file);
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
			dprintf(2, "error\n");
			exit (67);
		}
		if (ft_strcmp(cmd[nb]->stdout[i], ">") == 0)
			fd = ft_open_file(cmd[nb]->stdout[i + 1], fd, 1);
		else if (ft_strcmp(cmd[nb]->stdout[i], ">>") == 0)
			fd = ft_open_file(cmd[nb]->stdout[i + 1], fd, 2);
		else
		{
			dprintf(2, "unexpected error\n");
			exit (67);
		}
		i += 2;
	}
	return (fd);
}
