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

// managing heredoc
int	heredoc(char *cond)
{
	char	*line;
	int		pp[2];
	
	pipe(pp);
	while (1)
	{
		line = readline("> ");
		if(ft_strncmp(cond, line, ft_strlen(line)) == 0)
		{
			free(line);
			close(pp[1]);
			return(pp[0]);
		}
		write(pp[1], line, ft_strlen(line));
		write(pp[1], "\n", 1);
		free(line);
	}
}

// count how many heredoc
int	ft_nb_heredoc(t_cmd **cmd)
{
	int	i;
	int	j;
	int	nb_heredoc;

	i = 0;
	nb_heredoc = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i]->stdin[j])
		{
			if (ft_strcmp(cmd[i]->stdin[j], "<<") == 0)
				nb_heredoc++;
			j++;
		}
		i++;
	}
	return (nb_heredoc);
}

// return the name of the last file_in from simple redirection <
char	*ft_last_single_redir_in(t_cmd **cmd)
{
	int		i;
	int		j;
	char	*resu;

	i = 0;
	resu = NULL;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i]->stdin[j])
		{
			if (ft_strcmp(cmd[i]->stdin[j], "<") == 0)
			{
				if (cmd[i]->stdin[j + 1])
				{
					if (resu)
						free(resu);
					resu = ft_strdup(cmd[i]->stdin[j + 1]);
				}
			}
			j++;
		}
		i++;
	}
	return (resu);
}

// return type of the last redir: 0 is none, 1 is <, 2 is <<
int	ft_what_is_last_redir_in(t_cmd **cmd)
{
	int	i;
	int	j;
	int	resu;

	i = 0;
	resu = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i]->stdin[j])
		{
			if (ft_strcmp(cmd[i]->stdin[j], "<") == 0)
				resu = 1;
			else if (ft_strcmp(cmd[i]->stdin[j], "<<") == 0)
				resu = 2;
			j++;
		}
		i++;
	}
	return (resu);
}

// return the fd of the redir
int	ft_redir_in2(t_cmd **cmd)
{
	int		last_redir;
	int		fd;
	int		i;
	int		j;

	dprintf(2, "inside ft_redir_in2\n");
	last_redir = ft_what_is_last_redir_in(cmd);
	fd = 0;
	if (ft_nb_heredoc(cmd) != 0)
	{
		dprintf(2, "nb heredoc=[%d]\n", ft_nb_heredoc(cmd));
		i = 0;
		while (cmd[i])
		{
			j = 0;
			while(cmd[i]->stdin[j])
			{
				if (ft_strcmp(cmd[i]->stdin[j], "<<") == 0)
				{
					dprintf(2, "found heredoc << at i=[%d], j=[%d]\n", i, j);
					if (cmd[i]->stdin[j + 1] == NULL)
					{
						printf("minishell: syntax error near unexpected token `newline'\n");
						g_mini.ret_err = 258;
						return (1);
					}
					else
					{
						if (fd)
						{
							dprintf(2, "closing previous pipe fd=[%d]\n", fd);
							close(fd);
						}
						dprintf(2, "keyword=[%s][%s]\n", cmd[i]->stdin[j], cmd[i]->stdin[j + 1]);
						fd = heredoc(cmd[i]->stdin[j + 1]);
						dprintf(2, "new pipe open fd=[%d]\n", fd);
					}
				}
				j++;
			}
			i++;
		}
	dprintf(2, "end of all heredoc last fd=[%d]\n", fd);
	}
	if (last_redir == 0) // no redir
	{
		dprintf(2, "end of redir, no redir fd=0\n");
		return (0);
	}
	else if (last_redir == 1) // last is <
	{
		if (fd)
			close(fd);
		fd = open(ft_last_single_redir_in(cmd), O_RDONLY);
		dprintf(2, "end of redir, last redir is single fd=[%d]\n", fd);
		return (fd);
//		return (open(ft_last_single_redir_in(cmd), O_RDONLY));
	}
	else if (last_redir == 2) // last is <<
	{
		dprintf(2, "end of redir, last is heredoc fd=[%d]\n", fd);
		return (fd);
	}
	return (0);
}
