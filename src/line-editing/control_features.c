/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_features.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwojda <gwojda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 15:17:28 by gwojda            #+#    #+#             */
/*   Updated: 2017/03/16 14:05:00 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_buff_f6(void)
{
	int ret;

	ret = 0;
	read(0, &ret, sizeof(int));
}

void	ft_control_d(void)
{
	if (!STR || STR[0] == '\0')
	{
		ft_putstr("exit\n");
		builtin_exit(NULL, (char*[]){"exit", NULL}, NULL);
		data_singleton()->line.is_prompt ? ft_prompt() : ft_putstr("> ");
	}
	else if (POS < ft_strlen(STR))
		ft_del();
	else
		ft_puttermcaps("bl");
}

void	ft_control_c(void)
{
	if (STR)
		ft_current_str(STR, POS);
	ft_putchar('\n');
	set_exitstatus(1, 1);
	ft_prompt();
	ft_strdel(&STR);
	POS = 0;
}

void	ft_control_l(void)
{
	ft_clear_window();
	ft_prompt();
	ft_strdel(&STR);
	POS = 0;
}
