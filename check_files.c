/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:10:56 by atyurina          #+#    #+#             */
/*   Updated: 2024/04/12 14:10:57 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// проверяю файлы. если что не так - выхожу
/*
vars->out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
файлы на инпут, то есть откуда читать. если 
vars->in = open(argv[1], O_RDONLY);
*/

void	heredoc_err(t_data *vars, t_list *list)
{
	unlink(".heredoc_tmp");
	perror("file descriptor error\n");
	// FREE all malloced in structure before execution!!!!!!! 
	//нужно то что в листе замалочено убрать. временно сделаем это>>
	free(list);
	free_pipes(vars);
	exit(1);
}

int	hd(t_list *list, int *fd, char **buffer, char **line)
{
	char	*copy_line;
	int		i;

	copy_line = NULL;
	write(1, "pipe heredoc> ", 15);
	if (get_next_line(STDIN_FILENO, line, buffer) < 0)
		exit(1);
	i = ft_strchr_gnl(*line, '\n');
	if (i != -1)
	{
		copy_line = ft_strdup(*line);
		copy_line[i] = '\0';
	}
	if (!(ft_strncmp(copy_line, list->inf->file,
				ft_strlen(list->inf->file) + 1)))
	{
		free(*line);
		free(copy_line);
		return (0);
	}
	write(*fd, *line, ft_strlen(*line));
	free(*line);
	free(copy_line);
	return (1);
}

int	here_doc(t_data *vars, t_list *list)
{
	int			fd;
	char		*line;
	static char	*buffer;
	int			ret;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		heredoc_err(vars, list);
	ret = 1;
	while (ret == 1)
		ret = hd(list, &fd, &buffer, &line);
	free(buffer);
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
		heredoc_err(vars, list);
	unlink(".heredoc_tmp");
	return (fd);
}

void	check_out_files(t_list *list, t_data *vars)
{
	int	out_n;

	vars->out_file = -2;
	out_n = ft_outfsize(list->outf);
	while (out_n != 0 && list->outf != NULL)
	{
		if (list->outf->flag == 'a')
			vars->out_file = open(list->outf->file,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			vars->out_file = open(list->outf->file,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (vars->out_file == -1)
		{
			perror(list->outf->file); // no such file or directory or permission denied message. TEST!!!
			// FREE all malloced in structure before execution!!!!!!!
			free_pipes(vars);
			exit (1);
		}
		if (out_n - 1 != 0)
			close(vars->out_file);
		out_n--;
		list->outf = list->outf->next;
	}
}

//проверяю доступ к файлам. если их нет - создаю. 
void	check_in_files(t_list *list, t_data *vars)
{
	int	in_n;

	vars->in_file = -2;
	in_n = ft_infsize(list->inf);
	while (in_n != 0 && list->inf != NULL)			// return_builtin = builtin(list->cmd, list->argv, list->env);
			// if (return_builtin != 1042)
			// {
			// 	free_pipes(vars);
			// 	/// FREE all malloced before execution!
			// 	exit (return_builtin);
			// }
	{
		if (list->inf->flag == 'h')
			vars->in_file = here_doc(vars, list);
		else
		{
			vars->in_file = open(list->inf->file, O_RDONLY);
		}
		if (vars->in_file == -1)
		{
			perror(list->inf->file); // no such file or directory or permission denied message. TEST!!!
			// FREE all malloced in structure before execution!!!!!!!
			free_pipes(vars);
			exit (1);
		}
		if (in_n - 1 != 0)
			close(vars->in_file);
		in_n--;
		list->inf = list->inf->next;
	}
	check_out_files(list, vars);
}
