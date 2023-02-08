/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:21:09 by clecat            #+#    #+#             */
/*   Updated: 2023/02/08 21:23:58 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions
int	cotes_dollar(t_min *mini, char *line)
{
	if (verif_cotes(line) == 1)
	{
		free(mini->line);
		mini->line = ft_strdup(line);
		free(line);
		return (1);
	}
	return (0);
}

//verifie si dollar present et modifie mini.line en fonction
void	parcour_line(t_min *mini)
{
	char	*line;
	int		nb_dollar;

	nb_dollar = 0;
	nb_dollar = count_nbdollar(mini->line);
	if (nb_dollar == 0)
		return ;
	line = ft_strdup(mini->line);
	free(mini->line);
	mini->line = rm_d_dollar(line);
	free(line);
	nb_dollar = count_nbdollar(mini->line);
	line = ft_strdup(mini->line);
	if (cotes_dollar(mini, line) == 1)
		return ;
	free(mini->line);
	mini->line = ft_strdup(line);
	free(line);
	nb_dollar = count_nbdollar(mini->line);
	if (nb_dollar > 0)
	{
		line = ft_strdup(mini->line);
		free(mini->line);
		mini->line = modif_line(line, nb_dollar);
	}
}

//renvoie vers fonction de modif line
char	*modif_line(char *line, int nb_dollar)
{
	char	*tmp;
	char	*tmp2;

	if (line[0] == '$' && line[1] == '\0')
		return (line);
	tmp = ft_strdup(line);
	tmp2 = redir_line(tmp, nb_dollar);
	free(line);
	line = ft_strdup(tmp2);
	free(tmp2);
	return (line);
}

//faire fonction de redir cmd simple ou multiple
void	redir_pipe(t_min *mini, t_cmd **cmd)
{
	if (cmd[0]->cmd[0] == NULL && cmd[0]->stdin[0] == NULL
		&& cmd[0]->stdout[0] == NULL)
		return ;
	else
	{
		if (cmd[0]->cmd[0] == NULL && (cmd[0]->stdin != NULL
				|| cmd[0]->stdout != NULL))
			piping();
		else
		{
			if (ft_strcmp(cmd[0]->cmd[0], "exit") == 0 && cmd[1] == NULL)
				exit_min(mini, cmd[0]->cmd);
			else if (ft_strcmp(cmd[0]->cmd[0], "cd") == 0 && cmd[1] == NULL)
				cd(mini, cmd[0]->cmd);
			else if (ft_strcmp(cmd[0]->cmd[0], "export") == 0 && cmd[1] == NULL)
				export(mini, cmd[0]->cmd);
			else if (ft_strcmp(cmd[0]->cmd[0], "unset") == 0 && cmd[1] == NULL)
				unset(mini, cmd[0]->cmd);
			else
				piping();
		}
	}
}

//built-in : cd/echo/env/exit/export/unset
//redirige soit vers les built-in soit vers execve
void	redirection2(t_min *mini, t_cmd *cmd)
{
//	printf("cmd->cmd[0] = %s\n", cmd->cmd[0]);
	if (cmd->cmd[0] == NULL)
		return ;
	if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		exit_min(mini, cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		echo(cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		ft_env(mini, cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		cd(mini, cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		export(mini, cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		unset(mini, cmd->cmd);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		pwd(mini->c_env, cmd->cmd);
	else
		ft_set_pathexec2(mini, cmd->cmd);
}
