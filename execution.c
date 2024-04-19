/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtavabil <rtavabil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:51:44 by atyurina          #+#    #+#             */
/*   Updated: 2024/04/19 18:28:51 by rtavabil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	forking(t_list *list, t_data *vars)
{
	int	i;
//	int	return_builtin;

	i = 0;
	while (i < vars->lists_nbr && list != NULL)
	{
		vars->id = fork();
		if (vars->id == -1)
			ft_putstr_fd("Error while forking", 2);
		if (vars->id == 0)
		{
			printf("child process with id = %d\n", vars->id);
			check_in_files(list, vars);
			check_redirections(vars, list);
			redirect_stream(vars->in_file, vars->out_file);
			closing_pipes(vars);
			// return_builtin = builtin(list->cmd, list->argv, list->env);
			// if (return_builtin != 1042)
			// {
			// 	free_pipes(vars);
			// 	/// FREE all malloced before execution!
			// 	exit (return_builtin);
			// }
			now_execute(vars, list);
		}
		//printf("parent process with id = %d\n", vars->id);
		i++;
		list = list->next;
	}
}

int execute(t_list *list)
{
	t_data	vars;
	int		wstatus;

	vars.lists_nbr = ft_lstsize(list);
	create_pipes(&vars);
	forking(list, &vars);
	closing_pipes(&vars);
	free_pipes(&vars);
	//if (vars.id != 0 && vars.ex != 127) // если не ребенок и если не какой то спешл кейс 127. тогда ждем последний процесс, чтобы получить его экзит код и передаем
//	{ // может надо убрать про если не ребенок т.к. ребенок сюда точно не дойдет по-хорошему.
	waitpid(vars.id, &wstatus, 0);
	wait(NULL); ///wait for the rest of processes with while (nbr of processes - 1) {wait(NULL) i++;}.
	if (WIFEXITED(wstatus))
	{
		printf("exit status: %d\n", WEXITSTATUS(wstatus));
		return(WEXITSTATUS(wstatus)); //поменять на return;
	}
	return (0);
}