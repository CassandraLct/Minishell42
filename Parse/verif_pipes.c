/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:16:57 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/06 13:16:58 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

// return 1 if there is at least one double pipe : '| |'
int	is_there_double_pipe(char *line)
{
	int	i;
	int	len;

	len = ft_strlen(line);
	if (len < 3)
		return (0);
	i = 2;
	while (i < len)
	{
		if(line[i - 2] == '|' && line[i - 1] == ' ' && line[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

// return emplty line if pipe is in front or doubled
char	*verif_pipes(char *line)
{
	char	*new_line;

	new_line = NULL;
	new_line = remove_double_space(line);
	free(line);
	if (new_line[0] == '|' || is_there_double_pipe(line) == 1)
	{
		printf("%s|'\n", ERR_TOKEN_SHORT);
		g_mini.ret_err = 258;
		free(new_line);
		new_line = ft_calloc(1, sizeof(char));
		return (new_line);
	}
	return (new_line);
}
