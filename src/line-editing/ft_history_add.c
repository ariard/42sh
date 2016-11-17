/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 13:43:40 by jhalford          #+#    #+#             */
/*   Updated: 2016/11/10 13:43:50 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int		ft_history_add(t_data *data)
{
	t_dlist	*new;
	char	*str;

	str = data->input;
	if (data->history)
		while (data->history->next)
			data->history = data->history->next;
	if (!data->history->prev || ft_strcmp(str, (char *)data->history->prev->content))
	{
		new = ft_dlstnew(str, sizeof(char) * (ft_strlen(str) + 1));
		ft_dlstadd_before(&data->history, new);
		data->history = data->history->next;
		ft_strdel((char **)&data->history->content);
	}
	return (0);
}
