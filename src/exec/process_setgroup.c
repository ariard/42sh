/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_setgroup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 17:48:10 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/18 00:23:57 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

int		process_setgroup(t_process *p, pid_t pid)
{
	t_job	*j;
	t_data	*data;

	(void)p;
	data = data_singleton();
	j = &data->exec.job;
	if (!SH_IS_INTERACTIVE(data_singleton()->opts))
		return (0);
	DG("setpgid(%i, %i)", pid, j->pgid);
	if (setpgid(pid, j->pgid) == -1)
		ft_dprintf(2, "{red}%s: internal setpgid() errno=%i{eoc}\n", SHELL_NAME, errno);
	/* if (JOB_IS_FG(j->attrs)) */
	if (pid ==0 && JOB_IS_FG(j->attrs))
	{
		DG("tcsetpgrp[%i]", j->pgid);
		tcsetpgrp(STDIN, j->pgid);
		DG("after tcsetpgrp");
	}
	return (0);
}
