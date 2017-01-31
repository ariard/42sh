/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_while.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 17:33:53 by ariard            #+#    #+#             */
/*   Updated: 2017/01/31 20:45:41 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		exec_while(t_btree **ast)
{
	t_list		**test_commands;
	t_list		**consequent_commands;
	t_astnode	*node;
	t_process	*p;
	int			test;

	node = ((*ast)->left)->item;
	DG("test command data '%s'", node->data.str);
	test_commands = shell_get_ast(node->data.str);
//	ft_print_all_ast(*test_commands);
	node = ((*ast)->right)->item;

	DG("consequent command data '%s'", node->data.str);
	consequent_commands = shell_get_ast(node->data.str);
	
	p = &data_singleton()->exec.process;
	p->script |= SCRIPT_LOOP;

//	ft_print_all_ast(consequent_commands);

	test = 10;
	while (test--) 
		loop_exec(*consequent_commands);
//	del tree (test_commands);
//	del tree (test_commands);
	p->script &= 0;
	
	btree_delone(ast, &ast_free);	
	return (0);
}
