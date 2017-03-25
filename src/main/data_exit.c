/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jhalford@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 18:07:50 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/25 20:27:32 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	data_exit(void)
{
	t_data	*data;

	data = data_singleton();
	ft_strdel(&data->line.input);
	ft_strdel(&data->binary);
	exec_popfds();
	ft_sstrfree(data->env);
	ft_sstrfree(data->local_var);
	ft_sstrfree(data->argv);
	lexer_destroy(&data->lexer);
	parser_destroy(&data->parser);
	ft_lstdel(&data->jobc.first_job, &job_free);
	ft_lstdel(&data->lst_func, &tree_func_free);
	ft_save_termios(-1);
	ft_free_hash_table();
	free_history_list(data->line.list_beg);
	free(data_singleton());
}
