#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef long long		t_type;
typedef struct s_exec	t_exec;

struct s_exec
{
	t_type	type;
	int		(*f)(t_btree *ast, t_data *data);
};

extern t_exec	g_exec[];

int		ft_exec(t_btree *ast, t_data *data);

int		exec_semi(t_btree *ast, t_data *data);
int		exec_pipe(t_btree *ast, t_data *data);
int		exec_less(t_btree *ast, t_data *data);
int		exec_great(t_btree *ast, t_data *data);
int		exec_command(t_btree *ast, t_data *data);

#endif
