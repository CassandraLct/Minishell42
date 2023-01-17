/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:21:09 by clecat            #+#    #+#             */
/*   Updated: 2023/01/17 17:37:06 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//1 fonctions
//supprime les $$
void	rm_d_dollar(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(line));
	while(line[i])
	{
		if (line[i] == '$' && line[i + 1] == '$')
			i += 2;
		tmp[j] = line[i];
		j++;
		i++;
	}
	tmp[j] = '\0';
	free(line);
	line = ft_strdup(tmp);
	free(tmp);
}

//rempli le tab
void	recup_dollarvar(int nb_dollar)
{
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while(k != nb_dollar)
	{
		tmp = malloc(sizeof(char) * (ft_strlen(g_mini.line) + 1));
		while(g_mini.line[i] != '$')
			i++;
		i += 1;
		while(g_mini.line[i] != ' ' && g_mini.line[i] != '\0')
		{
			tmp[j] = g_mini.line[i];
			j++;
			i++;
		}
		tmp[j] = '\0';
		j = 0;
		i = 0;
		ft_dollar(tmp);
		free(tmp);
		k++;
	}
}

void	parcour_line(t_min *mini)
{
	int		i;
	int		nb_dollar;

	i = 0;
	nb_dollar = 0;
	rm_d_dollar(mini->line);
	while (mini->line[i])
	{
		if (mini->line[i] == '$')
			nb_dollar += 1;
		i++;
	}
	recup_dollarvar(nb_dollar);
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
