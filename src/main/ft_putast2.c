/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 18:18:04 by jhalford          #+#    #+#             */
/*   Updated: 2017/02/20 22:08:42 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putast2(void *nodein)
{
	t_astnode	*node;

	node = nodein;
	if (node->type == TK_SEMI)
		ft_putendl_fd("SEMI", 2);
	else if (node->type == TK_PIPE)
		ft_putendl_fd("PIPE", 2);
	else if (node->type == TK_COMMAND)
	{
		ft_putstr_fd("COMMAND: ", 2);
		ft_sstrprint_fd(2, node->data.sstr, ',');
		ft_putchar_fd('\n', 2);
	}
	else if (TK_REDIR(node->type))
	{
		ft_putnbr_fd(node->data.redir.n, 2);
		if (node->type == TK_GREATAND || node->type == TK_LESSAND)
		{
			if (node->type == TK_GREATAND)
				ft_putstr_fd(">&:", 2);
			else
				ft_putstr_fd("<&:", 2);
			ft_putnbr_fd(node->data.redir.word.fd, 2);
			if (node->data.redir.close)
				ft_putstr_fd(" (closed)", 2);
		}
		else
		{
			if (node->type == TK_GREAT)
				ft_putendl_fd(">:", 2);
			else if (node->type == TK_LESS)
				ft_putstr_fd("<:", 2);
			else if (node->type == TK_DGREAT)
				ft_putstr_fd(">>:", 2);
			else if (node->type == TK_DLESS)
				ft_putstr_fd("<<:", 2);
			ft_putstr_fd(node->data.redir.word.word, 2);
		}
		ft_putchar_fd('\n', 2);
	}
	else
		ft_putendl_fd("OTHER", 2);
}
