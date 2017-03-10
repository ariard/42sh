/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 14:54:45 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/10 15:37:47 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		set_process(t_process *p, t_btree *ast)
{
	t_exec		*exec;
//	t_cmd		*cmd;
	int			op;
	int			fds[2];

	exec = &data_singleton()->exec;
	op = pop(&exec->op_stack);
	if ((EXEC_IS_AND_IF(exec->attrs)
		&& ft_strcmp(ft_getenv(data_singleton()->env, "?"), "0") != 0)
	|| (EXEC_IS_OR_IF(exec->attrs)
		&& ft_strcmp(ft_getenv(data_singleton()->env, "?"), "0") == 0))
			return (1);
	fds[PIPE_WRITE] = STDOUT;
	fds[PIPE_READ] = STDIN;
	if (op == TK_PIPE)
	{
		pipe(fds);
		DG("[%i] -> PIPE -> [%i]", fds[PIPE_WRITE], fds[PIPE_READ]);
	}
	p->fdin = exec->fdin;
	p->to_close = fds[PIPE_READ];
	p->fdout = fds[PIPE_WRITE];
	exec->fdin = fds[PIPE_READ];
	p->redirs = ft_lstmap(((t_astnode *)ast->item)->data.cmd.redir, &redir_copy);
	return (set_process_map(p, ast));
}
