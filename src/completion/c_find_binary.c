/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_find_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alao <alao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 13:30:57 by alao              #+#    #+#             */
/*   Updated: 2017/03/23 19:07:52 by gwojda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

/*
** Retrieve the path from the env and create a char ** from the PATH pattern.
** The function will cycle through it to find the matching element using the
** c_parser() function.
*/

int			c_seek_binary(t_data *s, t_comp *c)
{
	char	*tmp;
	char	**paths;
	int		i;

	i = 0;
	tmp = NULL;
	if (!(tmp = ft_strdup(ft_getenv(s->env, "PATH"))))
		return (-1);
	paths = ft_strsplit(tmp, ':');
	if (c->match == NULL)
		c->match = ft_strdup(c->rcmd);
	while (paths[i])
		c_parser(c, paths[i++], c->rcmd);
	tmp ? ft_memdel((void *)&tmp) : (0);
	paths ? ft_sstrfree(paths) : (0);
	c_lst_id(data_singleton()->comp);
	return (0);
}
