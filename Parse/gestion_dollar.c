/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:51:02 by clecat            #+#    #+#             */
/*   Updated: 2023/01/23 15:27:19 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//4 fonctions
//change le $?
char	*var_reterr(char *line)
{
	char	*name_var;
	char	*tmp;
	
	name_var = ft_strdup(ft_itoa(g_mini.ret_err));
	tmp = NULL;
	if (ft_strncmp(name_var, "?", 1) == 0)
	{
		free(line);
		line = ft_strdup(name_var);
	}
	else
	{
		tmp = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(name_var)));
		tmp = change_line(name_var, line);
		free(line);
		line = ft_strdup(tmp);
		free(tmp);
	}
	free(name_var);
	return (line);
}

//change la val de la var existante
char	*var_true(char *line)
{
	char	*name_var;
	char	*tmp;

	printf("%s test \n", line);
	free(line);
	printf("%s test trhrthrthj \n", line);
	name_var = recup_namevar(line);
	printf("ici1\n");
	tmp = recup_valvar(name_var);
	printf("ici2, tmp = %s\n", tmp);
	free(name_var);
	printf("ici3\n");
	name_var = ft_strdup(tmp);
	printf("ici4\n");
	free(tmp);
	printf("ici5\n");
	tmp = change_line(name_var, line);
	printf("ici6\n");
	free(name_var);
	printf("ici7\n");
	free(line);
	printf("ici8\n");
	line = ft_strdup(tmp);
	printf("ici9\n");
	free(tmp);
	printf("ici10\n");
	return (line);
}

//supprime la var non-existante de la line
char	*var_false(char *line)
{
	char	*name_var;
	char	*tmp;

	name_var = malloc(sizeof(char) * 1);
	name_var[0] = '\0';
	tmp = change_line(name_var, line);
	free(name_var);
	free(line);
	line = ft_strdup(tmp);
	return (line);
}

//redirection vers les fonctions de modifications +25lignes
char	*redir_line(char *line, int nb_dollar)
{
	char	*tmp_line;

	// tmp_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
	tmp_line = ft_strdup(line);
	free(line);
	while (nb_dollar != 0)
	{
		if (verif_dollarcase(tmp_line) == 1) //$?
		{
			line = var_reterr(tmp_line);
			free(tmp_line);
			tmp_line = ft_strdup(line);
			nb_dollar -= 1;
		}
		else if (verif_dollarcase(tmp_line) == 2) //$PWD
		{
			line = var_true(tmp_line);
			//free(tmp_line);
			tmp_line = ft_strdup(line);
			nb_dollar -= 1;
		}
		else if (verif_dollarcase(tmp_line) == 3) //$pwd
		{
			line = var_false(tmp_line);
			free(tmp_line);
			tmp_line = ft_strdup(line);
			nb_dollar -= 1;
		}
	}
	return (line);
}
