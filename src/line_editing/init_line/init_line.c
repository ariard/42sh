/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwojda <gwojda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 17:34:44 by gwojda            #+#    #+#             */
/*   Updated: 2017/03/22 18:02:25 by gwojda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_line(void)
{
	data_singleton()->line.input = NULL;
	data_singleton()->line.copy_tmp = NULL;
	data_singleton()->line.pos_tmp = 0;
	data_singleton()->line.pos = 0;
	data_singleton()->line.prompt_size = 0;
	data_singleton()->line.list_size = 0;
	data_singleton()->line.list_end = NULL;
	data_singleton()->line.list_beg = NULL;
	data_singleton()->line.opt = 0;
}

void	readline_init(int has_prompt)
{
	static int	beg = 0;

	if (!beg)
	{
		ft_init_line();
		ft_init_history();
		ft_save_termios(1);
		beg = 1;
	}
	ft_init_termios();
	if (data_singleton()->line.input)
		ft_strdel(&data_singleton()->line.input);
	data_singleton()->line.list_cur = data_singleton()->line.list_beg;
	data_singleton()->line.pos = 0;
	has_prompt ? ft_prompt() : ft_putstr("> ");
	data_singleton()->line.is_prompt = has_prompt ? 1 : 0;
}
