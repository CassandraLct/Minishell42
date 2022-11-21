/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:21:09 by clecat            #+#    #+#             */
/*   Updated: 2022/11/17 11:10:07 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "src/minishell.h"

//split la line et stocker dans un char **tab;
/*char	split_line(char *line)
{}*/

/*int i = 0;int x = 0;int y = 0;*/
//test dup2 
int	main(void)
{
	char	*line;
	char	**tab;

	line = "minishell> cat test";
	while (line)
	{
		tab = ft_split(line, ' ');
	}
}
