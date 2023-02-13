/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:38 by clecat            #+#    #+#             */
/*   Updated: 2023/02/13 05:22:24 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions

//verifier si valeur deja presente
int	verif_modif_var(char **str, char *cmp)
{
	char	*name_var;
	char	*new_str;
	int		i;

	i = 0;
	name_var = recup_name(cmp);
	while (str[i])
	{
		new_str = ft_strjoin(str[i], "=");
		if (ft_strncmp(new_str, name_var, ft_strlen(name_var)) == 0)
		{
			free(new_str);//leaks
			free(name_var);
			return (1);
		}
		free(new_str);//leaks
		i++;
	}
	free(name_var);
	//free(new_str);//leaks
	return (0);
}

//redirige vers l'ajout ou la modification
void	new_vars(t_min *mini, char *str, int y, char **cmd)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) == 1 || str[0] == '=')
	{
		ft_print_error_msg3("minishell: export:`", cmd[y],
			"': not a valid identifier\n");
		mini->ret_err = 1;
		return ;
	}
	redir_changeval(mini, str);
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1] != '\0' && mini->nb_passage_exp == 0)
		{
			add_valenv(mini, str);
			add_valexp(mini, str);
			mini->nb_passage_exp += 1;
		}
		i++;
	}
	if (mini->nb_passage_exp == 0)
		add_valexp(mini, str);
	mini->nb_passage_exp = 0;
	mini->ret_err = 0;
}
