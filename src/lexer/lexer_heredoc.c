/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 15:51:17 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/08 23:19:57 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexer_heredoc(t_list **alst, t_lexer *lexer)
{
	t_token	*token;

	token = (*alst)->content;
	token->type = HEREDOCDATA;
	while (lexer->str[lexer->pos])
		if (token_append_char(token, lexer->str[lexer->pos++], 0, 0))
			return (1);
	return (0);
}