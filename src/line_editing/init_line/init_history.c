/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwojda <gwojda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 17:34:23 by gwojda            #+#    #+#             */
/*   Updated: 2017/03/21 10:39:24 by gwojda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_str_is_print(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isprint(str[i]))
			return (0);
		++i;
	}
	return (1);
}

static void		corrupt_history(int corrupt, char *home)
{
	if (corrupt)
		ft_dprintf(2, "42sh: corrupt history file %s/.42sh_history\n", home);
}

void			ft_init_history(void)
{
	int		fd;
	char	*str;
	char	*home;
	char	*path;
	char	corrupt;

	corrupt = 0;
	if (!(home = ft_getenv(data_singleton()->env, "HOME")))
		return ;
	path = ft_str3join(home, "/", ".42sh_history");
	if ((fd = open(path, O_RDONLY)) < 0)
		return (free(path));
	while (get_next_line(fd, &str) > 0)
	{
		if (ft_str_is_print(str) && *str)
			ft_push_back_history(&data_singleton()->line.list_beg,
												ft_create_history_list(str));
		else
			corrupt = CORRUPT;
		free(str);
	}
	corrupt_history(corrupt, home);
	free(path);
	free(str);
	close(fd);
}
