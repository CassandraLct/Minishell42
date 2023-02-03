/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/03 17:04:16 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// managing heredoc
int	heredoc(char *cond)
{
	char	*line;
	int		pp[2];

	pipe(pp);
//	pipe(g_mini.fd_hd);
//	dup2(STDIN_FILENO, g_mini.fd_hd[1]);
	while (1 && g_mini.sig_heredoc == 1)
	{
		// printf("dans heredoc\n");
//		ft_putstr_fd("> ", STDOUT_FILENO);
//		line = get_next_line(0);
		line = readline("> ");
		if (ft_strncmp(cond, line, ft_strlen(line)) == 0)
		{
			free(line);
			close(pp[1]);
			return (pp[0]);
		}
		write(pp[1], line, ft_strlen(line));
		write(pp[1], "\n", 1);
		free(line);
	}
	return (pp[0]);
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

// return the name of the file and an error message if can't open
void	ft_what_file(char *file, char **resu)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror(file);
	else
		close(fd);
	if (*resu)
		free(*resu);
	*resu = ft_strdup(file);
	return ;
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
					ft_what_file(cmd[i]->stdin[j + 1], &resu);
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
