/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:04:12 by atyurina          #+#    #+#             */
/*   Updated: 2024/04/19 18:07:39 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// возвращаю int - exit code
#include "minishell.h"

/* ECHO либо это Регина на этапе парсинга распишет,
либо мне надо самой расписать
atyurina@c2r6s1 ~> echo "hello\tworld"
hello\tworld
atyurina@c2r6s1 ~> echo hello\t world
hello	 world
atyurina@c2r6s1 ~> echo hello\t world \n
hello	 world 

atyurina@c2r6s1 ~> echo hello\t world '\n'
hello	 world \n

to compile:
cc -Wall -Wextra -Werror -g3 -gdwarf-3 built_in.c cd_builtin.c utils.c env_builtin.c echo_builtin.c export_builtin.c pwd_builtin.c
*/

int	builtin(char *cmd, char **argv, char ***env)
{
	int	i;
	int ret;

	i = 0;
	if ((ft_strcmp(cmd, "echo")) == 0)
		return (ft_echo(argv));
	if ((ft_strcmp(cmd, "cd")) == 0)
		return (ft_cd(argv, *env));
	if ((ft_strcmp(cmd, "pwd")) == 0)
		return (ft_pwd());
	if ((ft_strcmp(cmd, "export")) == 0)
	{
		ret = ft_export(argv, env);
		printf("im in builtin()\n");
		ft_env(*env);
		printf("im in builtin 2()\n");

		return (ret);
	}
	if ((ft_strcmp(cmd, "unset")) == 0)
		return (ft_unset(argv, *env));
	if ((ft_strcmp(cmd, "env")) == 0)
		return (ft_env(*env));
	if ((ft_strcmp(cmd, "exit")) == 0)
		return (ft_exit(argv));
	return (1042);
}

char	**duplicate_env(char **env)
{
	int		len;
	int		i;
	char	**dup_env;

	len = 0;
	i = 0;
	while (env[len] != NULL)
		len++;
	dup_env = ft_malloc((len + 1) * sizeof(char *));
	while (i < len)
	{
		dup_env[i] = ft_strdup(env[i]);
		if (dup_env[i] == NULL)
			return (NULL);//malloc error
		i++;
	}
	dup_env[i] = NULL;
	return (dup_env);
}

void	free_dup_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_data	data;
// 	int		return_value; //remove later

// 	return_value = 10; //remove later
// 	data.env = duplicate_env(env);
// 	if (data.env == NULL)
// 		return (1); //malloc error
// //	ft_env(data.env);
// 	if (argc > 1)
// 		return_value = (builtin(argv[1], argv + 2, &data));
// //	printf("\nexit code: %i", return_value); //remove later
// //	ft_env(data.env);
// 	free_dup_env(data.env);
// 	return (0);
// }
