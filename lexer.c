/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:21:09 by clecat            #+#    #+#             */
/*   Updated: 2022/11/08 10:37:39 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "src/minishell.h"

//split la line et stocker dans un char **tab;
/*char	split_line(char *line)
{}*/

//test dup2
int main()
{
	char *line;
	char **tab;
	/*int i = 0;
	int x = 0;
	int y = 0;*/

	line = "minishell> cat test";
	while(line)
	{
		tab = ft_split(line, ' ');
	}
}