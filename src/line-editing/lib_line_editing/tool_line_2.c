/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_line_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwojda <gwojda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 19:07:52 by gwojda            #+#    #+#             */
/*   Updated: 2017/02/05 17:06:07 by gwojda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_clear_window(void)
{
	pid_t	soon_pid;
	char	*tab_str[2];

	tab_str[0] = "/usr/bin/clear";
	tab_str[1] = NULL;
	soon_pid = fork();
	if (soon_pid != 0)
		wait(NULL);
	else
		execve("/usr/bin/clear", tab_str, data_singleton()->env);
}

static void	ft_read_tmp(void)
{
	int		ret;

	while (42)
	{
		ret = 0;
		read(0, &ret, sizeof(int));
		if (ret == TOUCHE_F6)
		{
			ret = 0;
			if (read(0, &ret, sizeof(int)) && ret == 126)
				break ;
		}
	}
}

void		ft_change_affichage(void)
{
	ft_putstr("\033[31m");
	ft_puttermcaps("cd");
	ft_puttermcaps("sc");
	ft_putstr(STR);
	ft_read_tmp();
	ft_puttermcaps("rc");
	ft_puttermcaps("cd");
	ft_putstr("\033[37m");
}

void		ft_printall(void)
{
	size_t	pos_tmp;
	int		ret;

	ret = 0;
	if (read(0, &ret, sizeof(int)) == -1 || ret != 126 || !STR)
		return ;
	ft_clear_window();
	ft_prompt();
	pos_tmp = POS;
	ft_change_affichage();
	if (POS)
		--POS;
	ft_get_beggin(STR, &POS);
	ft_current_str(STR, POS);
	ft_get_next_str(STR, &POS);
	if (POS && !STR[POS])
		--POS;
	if (POS)
		ft_putnc('\b', POS - pos_tmp + 1);
	POS = pos_tmp;
}

void		ft_get_beggin_with_curs(char *str, size_t *pos)
{
	while ((*pos) && str[(*pos)] != '\n')
	{
		--(*pos);
		ft_puttermcaps("le");
	}
	if (!*pos && str[(*pos)] != '\n')
		ft_puttermcaps("le");
	if (str[(*pos)] == '\n')
		++(*pos);
}