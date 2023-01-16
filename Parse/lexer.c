/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:21:09 by clecat            #+#    #+#             */
/*   Updated: 2023/01/16 16:53:55 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//1 fonctions

void	parcour_line(t_min *mini)
{
	char	*name;
	int		i;
	int		j;

	i = 0;
	j = 0;
	name = malloc(sizeof(char) * ft_strlen(mini->line));
	while(mini->line[i] != '$')
		i++;
	i += 1;
	while(mini->line[i] != ' ' && mini->line[i] != '\0')
	{
		name[j] = mini->line[i];
		j++;
		i++;
	}
	name[j] = '\0';
	printf("name = %s\n", name);
	ft_dollar(name);
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
