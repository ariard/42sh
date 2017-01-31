/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 17:28:14 by jhalford          #+#    #+#             */
/*   Updated: 2017/01/31 19:12:23 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char		**return_array_expand(t_ld *ld)
{
	char		**my_tab;
	int			index;
	char		**expand;
	char		**content;

	my_tab = NULL;
	while (ld)
	{
		content = ld->content;
	DG("EXPANSION DE :");
	DG("%s", content[0]);
		expand = glob(content[0], (unsigned char *)content[1]);
	DG();
		index = -1;
		while (expand[++index])
			my_tab = ft_sstradd(my_tab, expand[index]);
		ft_tabdel(&expand);
		ld = ld->next;
	}
	return (my_tab);
}

static void		ft_tabprint_fd(char **mytab, int fd)
{
	int		i;

	DG("Affichage des parametres envoyes apres le glob");
	if (!mytab || !*mytab)
		return ;
	i = 0;
	while (mytab[i])
	{
		ft_putendl_fd(mytab[i], fd);
		++i;
	}
}


int				exec_command(t_btree **ast)
{
	t_astnode	*node;
	t_process	*p;
	t_job		*job;

	node = (*ast)->item;
	p = &data_singleton()->exec.process;
	job = &data_singleton()->exec.job;
	p->av = return_array_expand(node->data.token);
	ft_tabprint_fd(p->av, 4);
	process_setexec(node->type, p);
	if (!(launch_process(p)))
	{
		job_addprocess(p);
		if (IS_PIPEEND(p->attributes))
		{
			JOB_IS_FG(job->attributes) ?
				put_job_in_foreground(job, 0):
				put_job_in_background(job, 0);
			job->pgid = 0;
		}
	}
	p->av = NULL;
	p->pid = 0;
	p->attributes = PROCESS_PIPESTART | PROCESS_PIPEEND;
	btree_delone(ast, &ast_free);
	return (0);
}
