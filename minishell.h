/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:45 by clecat            #+#    #+#             */
/*   Updated: 2022/11/14 12:53:32 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//includes
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_min
{
	char	**c_env;
	int		ret_error;
	char	*line;
	char	**tab;
	char	*prompt;
} g_min;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *str);
char	**ft_split(char const *s, char c);
void	recup_env(char **env, g_min mini);
int		strdigit(char *str);
void	print_env(g_min mini);
void	export(g_min mini);

#endif