/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:41:19 by atyurina          #+#    #+#             */
/*   Updated: 2024/04/19 18:07:53 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_data
{
	char	**env;
	int		exit_val;
	int		lists_nbr;
	int		pipes_nbr;
	int		**pipefd;
	int		in_file;
	int		out_file;
	int		id;
	char	**paths;
	char	*path;
}		t_data;
// в ребенке можно использовать переменныe под ребенка
// потому что процессы не шерят данные между собой

typedef struct s_inf
{
	char			flag; // 'h' 'c' 'n'. NULL whole struct if nothing given
	char			*file; // if 'h' them its a limiter //NULL if nothing given
	struct s_inf	*next;
}			t_inf;

typedef struct s_outf
{
	char			flag; // 'a' 'c' 'n'. NULL whole struct if nothing given
	char			*file; //NULL if nothing given
	struct s_outf	*next;
}			t_outf;

typedef struct s_list
{
	int				list_id;
	char			*cmd;
	char			**argv;
	char			**env;
	t_inf			*inf;
	t_outf			*outf;
	struct s_list	*next;
}				t_list;


//get_next_line:
int		get_next_line(int fd, char **line, char **buffer);
char	*return_line(char *buffer);
char	*get_buffer(int fd, char *buffer);
char	*trim_buffer(char *buffer);

//gnl_utils:
void	*ft_memcpy(void *dest, void *src, int n);
int		ft_strchr_gnl(char *s, int c);
char	*ft_substr(char *s, int start, int len);
void	*ft_calloc(int nmemb, int size);
void	ft_bzero(void *s, int n);

//execution:
int 	execute(t_list *list);
void	forking(t_list *list, t_data *vars);

//now_execute:
void	now_execute(t_data *vars, t_list *list);
void	check_redirections(t_data *vars, t_list *list);

//pipes_managing:
void	free_pipes(t_data *vars);
void	create_pipes(t_data *vars);
void	redirect_stream(int input, int output);
void	closing_pipes(t_data *vars);

//check_files:
void	check_in_files(t_list *list, t_data *vars);
void	check_out_files(t_list *list, t_data *vars);
int		hd(t_list *list, int *fd, char **buffer, char **line);
int		here_doc(t_data *vars, t_list *list);
void	heredoc_err(t_data *vars, t_list *list);

//check_cmd_access:
void	checking_access(t_data *vars, t_list *list);
void	check_path(t_data *vars, t_list *list, char **envp);
//utils:
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *str);
void	*ft_malloc(int size); //to be removed
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strcat(char *dest, char *src);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *nptr);

char	*ft_mystrncpy(char *dest, char *src, unsigned int n);

//utils_more:
int		ft_lstsize(t_list *lst);
int		ft_outfsize(t_outf *lst);
int		ft_infsize(t_inf *lst);
char	*ft_substr_split(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strjoin_three(char const *s1, char ch, char const *s2);

//built_in.c duplicating and freeind environment
int		builtin(char *cmd, char **argv, char ***env);
char	**duplicate_env(char **env);
void	free_dup_env(char **env);

//cd:
int		if_cd_luck(char **env);
int		cd_home(char **env);
int		cd_with_argv(char **argv, char **env);
int		ft_cd(char **argv, char **env);

//env:
int		ft_env(char **env);
char	*get_env_value(char **env, char *var, int len);
int		change_env_var(char **env, char *var, int len, char *new_value);

//echo:
int		ft_echo(char **argv);

//pwd:
int		ft_pwd(void);

//export:
void	add_env_var(char *arg, char **env);
void	add_str_arr(char *var, char ***env);
void	export_arg(char *arg, char ***env);
int		ft_export(char **argv, char ***env);

//unset:
int		ft_unset(char **argv, char **env);
int		unset_env_var(char **env, char *var, int len);

//exit:
int		ft_exit(char **argv);
void	check_argv_exit(char **argv, int exit_val);
int		is_sign(int c);
int		is_space(int c);
int		is_digit(int c);

#endif
