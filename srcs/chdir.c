/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 16:19:26 by taekkim           #+#    #+#             */
/*   Updated: 2020/11/30 16:19:28 by taekkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//char 	*get_path(t_all *a)
//{
//	char	*tmp;
//	int		i;
//
//	i = 0;
//	str = get_arg(str);
//	tmp = malloc(ft_strlen(str) + 1);
//	while (*str && *str == ' ')
//		str++;
//	while (*str && *str != ' ')
//		tmp[i++] = *str++;
//	tmp[i] = '\0';
//	return (tmp);
//}

int 	write_cd_error(char *str)
{
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}
int 	exec_cd(t_all *a)
{
	int i;

	i = 0;
	if (!ft_strncmp(a->arg[0], "~\0", 2) && !a->arg[1])
	{
		while (a->env[i])
		{
			if (!ft_strncmp(a->env[i], "HOME=", 5))
			{
				if (chdir(a->env[i] + 5) == -1)
					return (write_cd_error(a->env[i]));
			}
			i++;
			if (!a->env[i])
				return (0);
		}
	}
	else if (chdir(a->arg[0]) == -1)
		return (write_cd_error(a->arg[0]));
	return (0);
}

//void 	parse_cd(t_all *a)
//{
//	path = get_path(str + 3);
//	exec_cd(a);
//}

int 	cd(t_all *a)
{
	if (!ft_strncmp(a->cmd, "cd\0", 3))
	{
		if (!a->arg)
		{
			a->arg = malloc(sizeof(char *) * 2);
			a->arg[0] = ft_strdup("~");
			a->arg[1] = (void *)0;
			exec_cd(a);
			ft_free_mat(a->arg);
			return (1);
		}
		exec_cd(a);
		return (1);
	}
	return (0);
}
