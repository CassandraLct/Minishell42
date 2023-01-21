/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:25:45 by clecat            #+#    #+#             */
/*   Updated: 2023/01/21 12:33:12 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*---------INCLUDE-------------*/
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <termios.h>

/*----------STRUCTURE-----------*/
//structure tableau de cmd
typedef struct s_cmd
{
	char	**cmd;
	char	**stdin;
	char	**stdout;
}	t_cmd;

//main structure
typedef struct s_min
{
	t_cmd	**struct_cmd;
	char	**c_env;
	char	**c_exp;
	int		ret_err;
	char	*line;
	char	**tab;
	char	*prompt;
	int		nb_passage_exp;
	pid_t	pid;
	char	*val_home;
}	t_min;

t_min	g_mini;

/*--------------------------BUILT-IN-----------------------------------*/
//cd.c 5 fonctions
void	cd(t_min *mini, char **cmd);
void	change_value_pwd(char **str);
void	change_value_oldpwd(char **str, char *pwd, char *oldpwd);

//cd_tild.c 5 fonctions
void	change_valtab(t_min *mini, char **cmd);
char	*cd_tildpwd(char *str);
void	change_valcdtild(t_min *mini, char **cmd);
void	cd_noarg(t_min *mini);

//cd_utils.c 5 fonctions
int		check_arg(char *str);
char	*recup_pwd(char **str);
char	*recup_oldpwd(char **str);
void	cpy_value(char *name_var, char **str, char *new_val);

//chevrons.c
//echo.c 4 fonctions
void	echo(char **cmd);

//env.c 4 fonction
void	ft_env(t_min *mini, char **cmd);
void	change_val(char **str, char *new_pwd, char *pwd, char *oldpwd);
void	add_reponame(char **str, char *repo);

//exit_pwd.c 5 fonctions
void	exit_min(t_min *mini, char **cmd);
void	pwd(char **c_env, char **cmd);
int		recup_new_pwd(char **str);
void	change_val_pwdpath(char **str, char **cmd);

//export.c 5 fonctions
void	export(t_min *mini, char **cmd);
char	**order_exp(char **s1, char **s2);
int		verif_modif_var(char **str, char *cmp);

//export_addvar.c 3 fonctions
void	add_valexp(t_min *mini, char *str);
void	add_valenv(t_min *mini, char *str);

//export_change_val 5 fonctions
char	*recup_name(char *cmp);
void	redir_changeval(t_min *mini, char *str);

//export_utils.c 5 fonctions
void	print_export(char **str);
char	**fill_exp(char **new_val, char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		tablen(char **s1);
int		check_exp(char **s1, char **s2, int index);

//signaux.c
void	signaux(void);
void	signal_exit(void);
void	rl_replace_line(const char *text, int clear_undo);

//unset.c 4 fonctions
void	unset(t_min *mini, char **cmd);
int		check_var(char *str);

/*------------------------PARSE-------------------------------------------*/

//brouillon.c
char	*redir_gestdollar(int nb_dollar, t_min *mini);
char	*recup_dollarvar(char *line);
char	*rm_d_dollar(char *tmp);

//dollar_var 5 fonction
// void	ft_dollar(char *str);

//dollar_utils.c 
char	*recup_endline(int i, char *line);
char	*recup_startline(char *line);
// void	recup_dollarvar(int nb_dollar);
// void	rm_d_dollar(void);

//init.c 5 fonctions
void	init_struct(t_min *mini, char **envp);
void	init_export(t_min *mini);
void	free_all(t_min mini);
char	*recup_valhome(char	**c_env);
void	aff_err(char **cmd);

//lexer.c 2 fonctions
void	redir_pipe(t_min *mini, t_cmd **cmd);
void	redirection(t_min *mini, t_cmd **cmd);
void	parcour_line(t_min *mini);

//parse.c 4 fonctions
void	free_tab(char **tab);
char	**init_cpy(char **str, char **dest);
char	**ft_cpytab(char **tab);
char	**init_exp(char **tab);

// printstruc.c
void	printstruc(t_cmd *cmd);
void	printstruc2(t_cmd **cmd);

//splitcmd.c
t_cmd	**spliter3(char **inst);

//splitcmd_utils1.c
char	*remove_double_space(char *line);
int		count_cmd(char *line);
int		count_redir(char **list, char c);
int		count_all_redir(char *temp);
char	*ft_space_bracket(char *s);

// splitcmd_utils2.c
char	**ft_init_resu(char *line);
void	ft_copy_inside_simple_cote(char **res, char *line, int *i, int *j);
void	ft_copy_inside_double_cote(char **res, char *line, int *i, int *j);
t_cmd	*ft_malloc_resu(char **list);
void	free_t_cmd(void);

//splitline.c 3 fonctions
char	**spliter(void);

// splitline_utils.c
int		iscotevalid(char *line);
int		count_instruct(char *line);
void	*ft_test(void *var, void *error);
int		is_single_pipe(int j);

/*-----------------------UTILS--------------------------------------------*/

//itoa.c (libft)
char	*ft_itoa(int nb);

//ft_split.c (libft)
char	**ft_split(char const *s, char c);

//utils.c 5 fonctions
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(char *str);
int		strdigit(char *str);
int		ft_isdigit(char c);
char	*ft_strdup(char *s);

// utils2.c
int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, int n);

// utils3.c
char	*ft_strtrim(char *s1, char *set);
void	*ft_calloc(size_t count, size_t size);

/*-----------------------------------------------------------------------*/

//exec.c 5 fonctions
void	ft_exec(t_min *mini, char **all_path, char **pathcmd, char **cmd);
void	ft_set_pathexec(t_min *mini, char **cmd);

//exec_utils 2 fonctions
char	*recup_pathexec(t_min *mini);
int		aff_errcmd(char **cmd);
int		verif_cmd(char **all_path, char **pathcmd, char **cmd);

#endif