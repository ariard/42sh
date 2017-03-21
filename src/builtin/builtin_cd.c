/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jhalford@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 11:57:53 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/21 15:23:49 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define CDOPT_L	(1 << 0)
#define CDOPT_P	(1 << 1)
#define HAS_CDOPT_P(x) (x & CD_OPT_P)
#define HAS_CDOPT_L(x) (x & CD_OPT_L)
#define CDERR_1 "cd: no such file or directory: %s"
#define CDERR_2 "cd: HOME not set"
#define CDERR_3 "cd: too many arguments{eoc}"

static char		*builtin_cd_special(char *const av[], char *const env[])
{
	char	*target;

	if (!*av)
	{
		if (!(target = ft_getenv((char**)env, "HOME")))
		{
			SH_ERR(CDERR_2);
			return (NULL);
		}
	}
	else if (*av && *(av + 1))
	{
		SH_ERR(CDERR_3);
		return (NULL);
	}
	else if (ft_strcmp(*av, "-") == 0)
		target = ft_strdup(ft_getenv((char**)env, "OLDPWD"));
	else
		target = *av;
	return (target);
}

static int		builtin_cd_opts(char *const av[], int *opts)
{
	int		i;
	int		j;

	i = 1;
	if (av)
		while (av[i] && av[i][0] == '-' && av[i][1])
		{
			j = 0;
			while (av[i][++j])
			{
				if (av[i][j] == 'P')
					*opts = CDOPT_P;
				else if (av[i][j] == 'L')
					*opts = CDOPT_L;
				else if (av[i][j] == '-')
					return (i + 1);
				else
					return (i);
			}
			++i;
		}
	return (i);
}

int				builtin_cd(const char *path,
							char *const av[], char *const envp[])
{
	int		i;
	int		opts;
	char	*target;
	char	*cwd;

	opts = CDOPT_L;
	i = builtin_cd_opts(av, &opts);
	if (!(target = builtin_cd_special(av + i, envp)))
		return (builtin_return_status(0, 1));
	cwd = getcwd(NULL, 0);
	builtin_setenv(path, (char*[4]){"setenv", "OLDPWD", cwd, NULL}, envp);
	free(cwd);
	if (chdir(target))
	{
		SH_ERR(CDERR_1, target);
		return (builtin_return_status(0, 1));
	}
	else if (target != av[i])
		ft_printf("%s\n", target);
	cwd = getcwd(NULL, 0);
	builtin_setenv(path, (char*[4]){"setenv", "PWD", cwd, NULL}, envp);
	free(cwd);
	if (!ft_strcmp(*(av + i), "-"))
		free(target);
	return (builtin_return_status(0, 0));
}
