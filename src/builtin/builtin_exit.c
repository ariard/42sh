/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jhalford@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 14:28:41 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/24 23:35:26 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EXITERR_0 "exit: numeric argument required"
#define EXITERR_1 "exit: too many argument required"

int		builtin_exit(const char *path, char *const av[], char *const envp[])
{
	int			status;
	static int	notified = 0;

	(void)envp;
	(void)path;
	if (SH_HAS_JOBC(data_singleton()->opts) && !notified)
	{
		notified = 1;
		if (has_stopped_job() || has_running_job())
			return (SH_ERR("There are running and/or stopped jobs"));
	}
	if (av && av[1] && !ft_stris(av[1], ft_isdigit) && (status = 255))
		SH_ERR(EXITERR_0);
	else if (av && av[0] && av[1] && av[2])
		return (SH_ERR(EXITERR_1));
	else
		status = (av && av[1]) ?
			ft_atoi(av[1]) : ft_atoi(ft_getenv(data_singleton()->env, "?"));
	if (SH_IS_INTERACTIVE(data_singleton()->opts))
		tcsetattr(STDIN, TCSANOW, &data_singleton()->jobc.shell_tmodes);
	job_hup_all();
	data_exit();
	exit(status);
	return (0);
}
