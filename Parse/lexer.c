/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:21:09 by clecat            #+#    #+#             */
/*   Updated: 2023/01/20 16:56:55 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//4 fonctions

//faire une copie de la line avant ?
void	parcour_line(t_min *mini)
{
	// char	*line;
	char	*tmp;
	int		i;
	int		nb_dollar;

	i = 0;
	nb_dollar = 0;
	tmp = ft_strdup(mini->line);
	// free(mini->line);
	//mini->line = rm_d_dollar(tmp);
	while (mini->line[i])
	{
		if (mini->line[i] == '$')
			nb_dollar += 1;
		i++;
	}
	// line = redir_gestdollar(nb_dollar, mini);
	// free(g_mini.line);
	// g_mini.line = ft_strdup(line);
	// free(line);
	// printf("line5 = %s\n", g_mini.line);
	free(tmp);
	if(!g_mini.line)
		return ;
}

//built-in : cd/echo/env/exit/export/unset
//redirige soit vers les built-in soit vers execve
void	redirection(t_min *mini)
{
	if (mini->tab[0] == NULL)
		return ;
	if (ft_strcmp(mini->tab[0], "exit") == 0)
		exit_min(mini);
	else if (ft_strcmp(mini->tab[0], "echo") == 0)
		echo(mini);
	else if (ft_strcmp(mini->tab[0], "env") == 0)
		ft_env(mini);
	else if (ft_strcmp(mini->tab[0], "cd") == 0)
		cd(mini);
	else if (ft_strcmp(mini->tab[0], "export") == 0)
		export(mini);
	else if (ft_strcmp(mini->tab[0], "unset") == 0)
		unset(mini);
	else if (ft_strcmp(mini->tab[0], "pwd") == 0)
		pwd(mini->c_env);
	else
		ft_set_pathexec(mini);
}
