/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_access.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:59:43 by atyurina          #+#    #+#             */
/*   Updated: 2024/04/12 15:59:45 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_path(t_data *vars, t_list *list, char **envp)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	vars->paths = ft_split(envp[i] + 5, ':');
	j = 0;
	while (vars->paths[j] != NULL)
	{
		path = ft_strjoin_three(vars->paths[j], '/', list->cmd);
		if (access(path, X_OK) == -1)
		{
			j++;
			free(path);
		}
		else
		{
			vars->path = path;
			return ;
		}
	}
	vars->path = NULL;
	return ;
}

static int	found_sl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	checking_access(t_data *vars, t_list *list)
{
	int	i;

	i = 0;
	if (access(list->cmd, X_OK) != -1 || found_sl(list->cmd) == 1) //нужна ли эта found_sl вообще?
	{
		vars->path = list->cmd;
		return ;
	}
	else
	{
		check_path(vars, list, list->env);
		while (vars->paths[i] != NULL)
		{
			free(vars->paths[i]);
			i++;
		}
		free(vars->paths);
	}
	return ;
}
