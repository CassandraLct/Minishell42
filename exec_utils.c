/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 12:04:33 by clecat            #+#    #+#             */
/*   Updated: 2023/01/19 12:19:17 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//2 fonctions
//recupe path pour fonction recup_path
char	*recup_pathexec(t_min *mini)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (mini->c_env[i])
	{
		if (ft_strncmp(mini->c_env[i], "PATH=", 5) == 0)
		{
			tmp = ft_strdup(mini->c_env[i] + 5);
			break ;
		}
		i++;
	}
	return (tmp);
}

void	aff_errcmd(void)
{
	g_mini.ret_err = 127;
	printf("minishell: %s: command not found\n", g_mini.tab[0]);
	return ;
}
