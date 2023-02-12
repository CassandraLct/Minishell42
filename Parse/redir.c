/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/12 18:02:25 by rdi-marz         ###   ########.fr       */
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
			write(2, ERR_TOKEN, ft_strlen(ERR_TOKEN));
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

// return 1 if there is a dollar in the name
int	is_dollar_inside(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (file[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

// open file and return the fd
// close fd if allready open, open the file how=1 for > and how=2 for >>
int	ft_open_file(char *file, int fd, int how)
{
	if (is_dollar_inside(file) == 1)
	{
		g_mini.ret_err = 1;
		exit (1);
	}
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
		return (fd);
	}
	else if (fd == O_DIRECTORY)
	{
		ft_print_error_msg3("minishell: ", file, ": Is a directory\n");
		g_mini.ret_err = 1;
		exit (1);
	}
	return (fd);
}
