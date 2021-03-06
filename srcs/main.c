/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 20:08:53 by taekkim           #+#    #+#             */
/*   Updated: 2020/12/04 14:11:37 by taehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <string.h>

void sig_handle(int signo)
{
	if (signo == SIGINT)
		ft_write("\nbash-3.2$ ");
}

char	*get_cmd(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			break ;
		i++;
	}
	if (i > 0)
		return (strndup(str, i));
	return (ft_strdup(""));
}
int 	cmd_exec(t_all *a)
{
	char **lines;
	char *path_cmd;
	char *path_cmd2;
	char **tmp;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		path_cmd = ft_strjoin("/bin/", a->cmd);
		path_cmd2 = ft_strjoin("/usr/bin/", a->cmd);
		tmp = malloc(sizeof(char *) * 2);
		tmp[0] = ft_strdup(a->cmd);
		tmp[1] = (void *)0;
		lines = ft_matjoin(tmp, a->arg);
		if ((execve(path_cmd, lines, a->env) == -1) &&
			execve(path_cmd2, lines, a->env) == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(a->cmd, 2);
			ft_putendl_fd(": command not found", 2);
		}
		free(path_cmd);
		free(path_cmd2);
		free(lines);
		exit(0);
	}
	else if (pid == -1)
	{
		printf("%s\n", strerror(errno));
		exit(1);
	}
	waitpid(pid, 0, 0);
	return (1);
}

int     cmd_builtin(t_all *a)
{
	if (!(a->cmd))
		return (0);
	ft_exit(a);
    if (export(a) || cd(a) || pwd(a) || env(a) || unset(a) || echo(a))
	    return (1);
    return (0);
}

int 	main_loop(t_all *a)
{
	parsing(a);
	// validate();
	/*
	 * export a | grep a
	 * cmd export
	 * argument[0] a
	 * a->p.pipe = 1
	 */
	if (a->p.pipe)
	{
		ft_pipe(a);
		return (0); //no more pipe
	}
	redirect(a);
	if (cmd_builtin(a) || cmd_exec(a))
		return (1);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	t_all *a;
	char *tmp;
	(void)argc;
	(void)argv;

	a = malloc(sizeof(t_all));
	signal(SIGINT, sig_handle);
	signal(SIGQUIT, sig_handle);
	init_env(envp, a);
	init_export(a, a->env);
	while (ft_write(INIT) && get_next_line(0, &(a->line)) > 0)
	{
		if (!a->line[0])
		{
			free(a->line);
			continue ;
		}
		tmp = a->line;
		init(a);
		init_index(a);
		main_loop(a);
		if (a->redirect)
			dup2(a->fd_tmp, a->fileno);
		free(tmp);
		tmp = (void *)0;
	}
	return (0);
}
//
//int main(int argc, char *argv[], char *envp[])
//{
//	t_all a;
//	(void)argc;
//	(void)argv;
//
//	signal(SIGINT, sig_handle);
//	signal(SIGQUIT, sig_handle);
//	init_env(envp, &a);
//	init_export(&a, a.env);
//	while (ft_write(INIT) && get_next_line(0, &a.line) > 0)
//	{
//		main_loop(&a);
//		if (a.redirect)
//       		dup2(a.fd_tmp, a.fileno);
//		free(a.line);
//		a.line = (void *)0;
//	}
//	return (0);
//}
//
