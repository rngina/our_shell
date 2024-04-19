/* ************************************************************************** */
/*	*/
/*	:::	  ::::::::   */
/*   export_builtin.c	   :+:	  :+:	:+:   */
/*	+:+ +:+	 +:+	 */
/*   By: atyurina <marvin@42.fr>	+#+  +:+	   +#+	*/
/*	+#+#+#+#+#+   +#+	   */
/*   Created: 2024/04/01 17:12:44 by atyurina	  #+#	#+#	 */
/*   Updated: 2024/04/01 17:12:46 by atyurina	 ###   ########.fr	   */
/*	*/
/* ************************************************************************** */

/*
you can export multiple variables:
export VAR1=value1 VAR2=value2 VAR3=value3 
(it does not have to be capslock. can be any) 
между ними могут быть рандомные стринги и они просто проигнортся. 
а везде где есть равно - становится в env
also is you pass just a string without = it just doesnt impact
*/

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	add_str_arr(char *var, char ***env)
{
	int		len;
	int		i;
	char	**dup_env;

	ft_env(*env);
	printf("I entered add_str_arr\n");
	len = 0;
	i = 0;
	while ((*env)[len] != NULL)
		len++;
	printf("len after while %d\n", len);
	dup_env = (char **)malloc((len + 2) * sizeof(char *));
	while (i < len)
	{
		dup_env[i] = ft_strdup((*env)[i]);
		printf("\033[1;32m  dup_env[%d]=%s  \033[0m\n", i,  dup_env[i]); 
		i++;
	}
	dup_env[i] = ft_strdup(var);
	printf("\033[1;32m  dup_env[%d]=%s  \033[0m\n", i,  dup_env[i]); 
	dup_env[i + 1] = NULL;
	free_dup_env(*env);
	*env = dup_env;
}

void	add_env_var(char *arg, char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	env[i] = ft_strdup(arg);
	env[i + 1] = NULL;
}

void	export_arg(char *arg, char ***env)
{
	int		i;
	int		j;
	char	*var;
	int		exist;

	printf("from export_arg() *env=%s\n", **env);
	if (ft_strchr(arg, '=') == NULL)
		return ;
	else
		i = ft_strchr(arg, '=') - arg;
	exist = 0;
	var = (char *)ft_malloc((i + 1) * sizeof(char));
	var = ft_mystrncpy(var, arg, i);
	printf("var = %s\n", var);
	j = 0;
	while ((*env)[j] != NULL)
	{
		if (change_env_var(*env, var, i, arg + i) == 0)
		{
			exist = 1;
			break ;
		}
		j++;
	}
	printf("from export_arg() after while *env=%s\n", **env);
	if (exist == 0)
	{
		printf("im inside export_arg() inside if(exist==0)\n");
		printf("from export_arg() inside if(exist == 0) after add_str_arr() *env=%s\n", **env);
		add_str_arr(arg, env);
		printf("from export_arg() inside if(exist == 0) after add_str_arr() *env=%s\n", **env);
		printf("im inside export_arg() inside if(exist==0) 2\n");
	}
	free(var);

	ft_env(*env);
}

int	ft_export(char **argv, char ***env)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		export_arg(argv[i], env);
		i++;
	}
	printf("from ft_export\n");
	ft_env(*env);
	printf("from ft_export 2\n");
	return (0);
}
