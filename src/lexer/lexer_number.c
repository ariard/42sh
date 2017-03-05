/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 12:06:45 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/05 16:03:31 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		lexer_number(t_list **alst, t_lexer *lexer)
{
	t_token		*token;
	t_lexstate	state;

	token = (*alst)->content;
	token->type = TK_IO_NUMBER;
	if ((state = get_state_global(lexer))
			|| (state = get_state_redir(lexer)))
	{
		lexer->state = state;
		return (lexer_lex(alst, lexer));
	}
	else if (ft_isdigit(lexer->str[lexer->pos])
			&& (ft_isdigit(lexer->str[lexer->pos + 1])
				|| lexer->str[lexer->pos + 1] == '>'
				|| lexer->str[lexer->pos + 1] == '<'))
	{
		token_append(token, lexer, 0, 0);
		lexer->pos++;
		return (lexer_number(alst, lexer));
	}
	else
	{
		token->type = TK_WORD;
		token_append(token, lexer, 0, 0);
		lexer->pos++;
		return (lexer_lex(alst, lexer));
	}
	lexer->state = DEFAULT;
	return (lexer_lex(alst, lexer));
}
/*
int		lexer_number(t_list **alst, t_lexer *lexer)
{
	t_token		*token;
	t_lexstate	state;

	token = (*alst)->content;
	token->type = TK_IO_NUMBER;
	if ((state = get_state_global(lexer))
			|| (state = get_state_redir(lexer)))
	{
		lexer->state = state;
		return (lexer_lex(alst, lexer));
	}
	else if (ft_isdigit(lexer->str[lexer->pos])
		&& (lexer->str[lexer->pos + 1] == '>' || lexer->str[lexer->pos + 1] == '<'))
	{
		token_append(token, lexer, 0, 0);
		lexer->pos++;
		return (lexer_number(alst, lexer));
	}
	else
	{
		token->type = TK_WORD;
		token_append(token, lexer, 0, 0);
		lexer->pos++;
		return (lexer_lex(alst, lexer));
	}
	lexer->state = DEFAULT;
	return (lexer_lex(alst, lexer));
}
*/
