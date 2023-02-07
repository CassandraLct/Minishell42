/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_change_val.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:03:34 by clecat            #+#    #+#             */
/*   Updated: 2023/02/06 11:19:52 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//change la valeur dans env, la valeur ne change pas si pas de egal
void	changeval_env(char **c_env, char *str)
{
	char	*name_var;
	int		i;

	i = 0;
	name_var = recup_name(str);
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
	if (i != tablen(c_env))
		i++;
	free(name_var);
}

//change la valeur dans export
void	changeval_exp(char **c_exp, char *str)
{
	char	*name_var;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	name_var = malloc(sizeof(char) * (i + 1));
	while (str[i] != '=')
	{
		name_var[i] = str[i];
		i++;
	}
	name_var[i] = '\0';
	i = 0;
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
	printf("dans redir_changeval\n");
	if (verif_modif_var(mini->c_env, str) == 1
		&& verif_modif_var(mini->c_exp, str) == 1)
	{
		printf("present dans env et exp\n");
		changeval_exp(mini->c_exp, str);
		changeval_env(mini->c_env, str);
		mini->nb_passage_exp += 1;
	}
	else if (verif_modif_var(mini->c_exp, str) == 1
		&& verif_modif_var(mini->c_env, str) == 0)
	{
		printf("present dans exp\n");
		changeval_exp(mini->c_exp, str);
		add_valenv(mini, str);
		mini->nb_passage_exp += 1;
	}
}

//recupere le nom de la variable
char	*recup_name(char *cmp)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	printf("cmd= %s\n", cmp);
	if (check_var(cmp) == 1)
	{
		tmp = malloc(sizeof(char) * (ft_strlen(cmp) + 1));
		while (cmp[i] && cmp[i] != '=')
		{
			tmp[i] = cmp[i];
			i++;
		}
		tmp[i] = cmp[i];
		tmp[i + 1] = '\0';
	}
	else if (check_var(cmp) == 0)
		tmp = addegal(cmp);
	return (tmp);
}

char	*addegal(char *cmp)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char) * ft_strlen(cmp) + 1);
	while (cmp[i])
	{
		tmp[i] = cmp[i];
		i++;
	}
	tmp[i] = '=';
	tmp[i + 1] = '\0';
	return (tmp);
}
