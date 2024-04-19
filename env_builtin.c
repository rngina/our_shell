/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:43:55 by atyurina          #+#    #+#             */
/*   Updated: 2024/04/19 17:56:13 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		// if (i == 0)
		// 	ft_putstr_fd("ch\n", 1);
		printf("\033[1;34m %s \033[0m\n", env[i]);
		i++;
	}
	return (0);
}

char	*get_env_value(char **env, char *var, int len)
{
	int	i;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], var, len) != 0)
		i++;
	return (env[i] + (len));
}

int	change_env_var(char **env, char *var, int len, char *new_value)
{
	int	i;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], var, len) != 0)
		i++;
	if (env[i] == NULL)

		return (1);
	else
	{
		free(env[i]);
		env[i] = ft_malloc(len + ft_strlen(new_value) + 1);
		ft_strcpy(env[i], var);
		ft_strlcat(env[i], new_value, len + ft_strlen(new_value) + 1);
		return (0);
	}
}
