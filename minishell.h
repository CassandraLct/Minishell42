/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:45 by clecat            #+#    #+#             */
/*   Updated: 2022/11/25 16:39:15 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//includes
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_min
{
	char	**c_env;
	char	**c_exp;
	int		ret_err;
	char	*line;
	char	**tab;
	char	*prompt;
	char	*cdpath;
}	t_min;

//utils.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *str);
int		strdigit(char *str);
int		ft_isdigit(char c);
char	*ft_strdup(char *s);

//ft_split.c
char	**ft_split(char const *s, char c);

//env.c
void	ft_env(t_min mini);

//export.c
void	export(t_min mini);
void	order_exp(t_min mini);

//export_utils.c
void	print_export(char **str);
void	fill_exp(t_min mini, char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		check_exp(t_min mini, int index);
int		tablen(t_min mini);

//echo.c
void	echo(t_min mini);

//parse.c
void	free_tab(char **tab);
char	**init_cpy(char **str, char **dest);
char	**ft_cpytab(char **tab);
char	**init_exp(char **tab);

//cd.c
void	cd(t_min mini);

//exit_pwd.c
void	exit_min(t_min mini);
void	pwd(char **c_env);

//init.c
t_min	init_struct(t_min mini, char **envp);
char	**init_export(t_min mini);

//unset.c
void	unset(t_min mini);

//exec.c
void	ft_exec(t_min mini);

//lexer.c
char	**split_line(t_min mini);
void	redirection(t_min mini);

#endif