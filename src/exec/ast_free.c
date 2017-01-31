/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 11:50:51 by jhalford          #+#    #+#             */
/*   Updated: 2017/01/31 18:49:37 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ast_free(void *data, size_t content_size)
{
	t_astnode	*node;

	(void)content_size;
	node = data;
	if (node->type == TK_COMMAND)
	{
		if (node->data.sstr)
			ft_sstrfree(node->data.sstr);
	}
	else if (node->type == TK_LESS || node->type == TK_GREAT || node->type == TK_DGREAT)
	{
		ft_strdel(&node->data.redir.word.word);
	}
}
