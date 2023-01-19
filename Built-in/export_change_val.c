/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_change_val.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:03:34 by clecat            #+#    #+#             */
/*   Updated: 2023/01/19 17:46:31 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//ajoute le egal
char	*add_egal(char *name_var, char *str)
{
	int	i;

	i = 0;
	if (check_var(str) != 1)
		return (name_var);
	else
	{
		while (name_var[i])
		{
			i++;
		}
		name_var[i] = '=';
		name_var[i + 1] = '\0';
	}
	return (name_var);
}

//change la valeur dans env, la valeur ne change pas si pas de egal
void	changeval_env(char **c_env, char *str)
{
	char	*name_var;
	int		i;

	i = 0;
	name_var = recup_name(str);
	name_var = add_egal(name_var, str);
	while (c_env[i])
	{
		if (check_var(name_var) != 1)
		{
			free(name_var);
			return ;
		}
		else
		{
			if (ft_strncmp(c_env[i], name_var, ft_strlen(name_var)) == 0)
			{
				free(c_env[i]);
				c_env[i] = ft_strdup(str);
			}
			i++;
		}
	}
	free(name_var);
	if (i != tablen(c_env))
		i++;
}

//change la valeur dans export
void	changeval_exp(char **c_exp, char *str)
{
	char	*name_var;
	int		i;

	i = 0;
	name_var = recup_name(str);
	while (c_exp[i])
	{
		if (ft_strncmp(c_exp[i], name_var, ft_strlen(name_var)) == 0)
		{
			free(c_exp[i]);
			c_exp[i] = ft_strdup(str);
		}
		i++;
	}
	free(name_var);
	if (i != tablen(c_exp))
		i++;
}

//redirige vers les fonctions de modification ou d'ajout
void	redir_changeval(t_min *mini, char *str)
{
	if (verif_modif_var(mini->c_env, str) == 1
		&& verif_modif_var(mini->c_exp, str) == 1)
	{
		changeval_exp(mini->c_exp, str);
		changeval_env(mini->c_env, str);
		mini->nb_passage_exp += 1;
	}
	else if (verif_modif_var(mini->c_exp, str) == 1
		&& verif_modif_var(mini->c_env, str) == 0)
	{
		changeval_exp(mini->c_exp, str);
		add_valenv(mini, str);
		mini->nb_passage_exp += 1;
	}
}

//recupere le nom de la variable
char	*recup_name(char *cmp)
{
	char	*tmp;
	int	i;

	i = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(cmp) + 1));
	if (check_var(cmp) == 1)
	{
		while (cmp[i] != '=')
		{
			tmp[i] = cmp[i];
			i++;
		}
		tmp[i] = cmp[i];
		tmp[i] = '\0';
		if (cmp[i] != '\0')
			i++;
	}
	else if (check_var(cmp) == 0)
	{
		while (cmp[i])
		{
			tmp[i] = cmp[i];
			i++;
		}
		tmp[i] = '\0';
	}
	return (tmp);
}
