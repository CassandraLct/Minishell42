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

// return the name of the last file-in from simple redirection <
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

int	ft_redir_in2(t_cmd **cmd)
{
	int		last_redir;

	dprintf(2, "inside ft_redir_in2\n");
	last_redir = ft_what_is_last_redir_in(cmd);
	if (ft_nb_heredoc(cmd) != 0)
	{
		// heredoc
	}
	if (last_redir == 0) // no redir
	{

	}
	else if (last_redir == 1) // last is <
	{

	k = ft_last_single_redir_in(cmd);
	}
	else if (last_redir == 2) // last is <<
	{

	}
	return (0);
}
