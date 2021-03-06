#include "../inc/minishell.h"

int 	ft_pipe(t_all *a)
{
	pid_t pid;
	pid_t pid2;

	if (pipe(a->fd) == -1)
		bash_cmd_error("pipe", "pipe < 0", 1);
	pid = fork();
	if (pid < 0)
		bash_cmd_error("pid", "pid < 0", 1);
	else if (pid == 0)
	{
		dup2(a->fd[1], STDOUT_FILENO);
		close(a->fd[0]);
		close(a->fd[1]);
		redirect(a);
		if (cmd_builtin(a) || cmd_exec(a))
			exit(0);
		exit(0);
	}
	pid2 = fork();
	if (pid2 < 0)
		bash_cmd_error("pid", "pid < 0", 1);
	else if (pid2 == 0)
	{
		dup2(a->fd[0], STDIN_FILENO);
		close(a->fd[0]);
		close(a->fd[1]);
		/*
		 * only one pipe
		 */
		free_com_arg(a);
		main_loop(a);
		exit(0);
	}
	close(a->fd[0]);
	close(a->fd[1]);
	waitpid(pid2, 0, 0);
	return (0);
}
