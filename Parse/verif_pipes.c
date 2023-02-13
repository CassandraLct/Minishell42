/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:16:57 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/13 13:03:13 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//2 fonctions
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
		if (line[i - 2] == '|' && line[i - 1] == ' ' && line[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

// return emplty line if pipe is in front, at the end or doubled
char	*verif_pipes(char *line)
{
	char	*new_line;
	int		len;

	new_line = NULL;
	new_line = remove_double_char_q(line, ' ');
	free(line);
	len = ft_strlen(new_line);
	if (new_line[0] == '|' || is_there_double_pipe(new_line) == 1)
	{
		printf("%s|'\n", ERR_TOKEN_SHORT);
		g_mini.ret_err = 258;
		free(new_line);
		new_line = ft_calloc(1, sizeof(char));
		return (new_line);
	}
	if (new_line[len - 1] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		g_mini.ret_err = 258;
		free(new_line);
		new_line = ft_calloc(1, sizeof(char));
		return (new_line);
	}
	return (new_line);
}
