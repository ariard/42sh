/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_cut_paste.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwojda <gwojda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 12:45:06 by gwojda            #+#    #+#             */
/*   Updated: 2017/03/22 20:58:12 by gwojda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_term(char **str, size_t *pos)
{
	size_t pos_ref;

	pos_ref = *pos;
	if (*pos)
	{
		--(*pos);
		ft_get_beggin_with_curs(*str, pos);
	}
	ft_puttermcaps("cd");
	ft_current_str(*str, *pos);
	ft_get_next_str(*str, pos);
	ft_putnc('\b', *pos - pos_ref);
	(*pos) = pos_ref;
}

static void	reset_and_remove_term(char **str, size_t *pos, char *copy_tmp)
{
	size_t pos_ref;

	pos_ref = *pos;
	if (!data_singleton()->line.pos_tmp)
		pos_ref += ft_strlen(data_singleton()->line.copy_tmp);
	while (*copy_tmp)
	{
		--pos_ref;
		*str = ft_remove_imput(*str, pos_ref);
		++copy_tmp;
	}
	if (*pos)
	{
		--(*pos);
		ft_get_beggin_with_curs(*str, pos);
	}
	ft_puttermcaps("cd");
	ft_current_str(*str, *pos);
	ft_get_next_str(*str, pos);
	ft_putnc('\b', *pos - pos_ref);
	(*pos) = pos_ref;
}

int			ft_x(char **str, size_t *pos)
{
	int		ret;
	size_t	pos_ref;

	pos_ref = *pos;
	ft_strdel(&data_singleton()->line.copy_tmp);
	data_singleton()->line.pos_tmp = 0;
	if (!*str)
		return (0);
	while (42)
	{
		ret = 0;
		if (read(STDIN, &ret, sizeof(int)) < 0)
			return (-1);
		if ((*str)[*pos] == '\n')
			return (0);
		if (ret == FLECHE_GAUCHE)
			underline_left(str, pos, pos_ref);
		else if (ret == FLECHE_DROITE)
			underline_right(str, pos, pos_ref);
		else
			break ;
	}
	if (data_singleton()->line.copy_tmp && *data_singleton()->line.copy_tmp)
		reset_and_remove_term(str, pos, data_singleton()->line.copy_tmp);
	return (0);
}

int			ft_c(char **str, size_t *pos)
{
	int		ret;
	size_t	pos_ref;

	pos_ref = *pos;
	ft_strdel(&data_singleton()->line.copy_tmp);
	data_singleton()->line.pos_tmp = 0;
	if (!*str)
		return (0);
	while (42)
	{
		ret = 0;
		if (read(STDIN, &ret, sizeof(int)) < 0)
			return (-1);
		if ((*str)[*pos] == '\n')
			return (0);
		if (ret == FLECHE_GAUCHE)
			underline_left(str, pos, pos_ref);
		else if (ret == FLECHE_DROITE)
			underline_right(str, pos, pos_ref);
		else
			break ;
	}
	reset_term(str, pos);
	return (0);
}

int			ft_v(char **str, size_t *pos)
{
	size_t	tmp_pos;
	int		i;
	char	*tmp;

	i = -1;
	tmp_pos = *pos;
	tmp = data_singleton()->line.copy_tmp;
	if (!*str || !tmp)
		return (0);
	while (tmp[++i])
	{
		if (ft_strlen(*str) > SIZE_LINE)
			break ;
		*str = ft_realloc_imput(*str, tmp[i], *pos + i);
	}
	if (*pos)
	{
		--(*pos);
		ft_get_beggin_with_curs(*str, pos);
	}
	ft_current_str(*str, *pos);
	ft_get_next_str(*str, pos);
	ft_putnc('\b', *pos - tmp_pos);
	*pos = tmp_pos;
	return (0);
}
