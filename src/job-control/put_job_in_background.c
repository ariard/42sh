/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_job_in_background.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:03:29 by jhalford          #+#    #+#             */
/*   Updated: 2017/02/20 21:52:28 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

int		put_job_in_background(t_job *j, int cont)
{
	if (cont)
		if (kill(-j->pgid, SIGCONT) < 0)
			DG("kill(SIGCONT) failed");
	return (0);
}
