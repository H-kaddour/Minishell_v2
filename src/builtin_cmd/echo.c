/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:15:12 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/23 18:52:58 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_nline_option(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	while (!ft_strncmp(cmd[i], "-n", 2))
	{
		j = 2;
		while (cmd[i][j])
		{
			if (cmd[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
		if (!cmd[i])
			return (i);
	}
	return (i);
}

static void	echo_home_env(t_data *data, t_cmd *trav, int i)
{
	char	*home;

	home = getenv("HOME");
	if (home)
		home = add_join(data, home, &trav->cmd[i][1], 1);
	else
		home = add_dup(data, &trav->cmd[i][1], 1);
	ft_putstr_fd(home, trav->f_out);
	ft_putchar_fd(' ', trav->f_out);
}

static void	echo_helper(t_data *data, t_cmd *trav, int i)
{
	if (trav->cmd[i][0] == '~' && \
			(trav->cmd[i][1] == '/' || !trav->cmd[i][1]))
		echo_home_env(data, trav, i);
	else
	{
		ft_putstr_fd(trav->cmd[i], trav->f_out);
		if (trav->cmd[i + 1])
			ft_putchar_fd(' ', trav->f_out);
	}
}

void	echo_cmd(t_data *data, t_cmd *trav)
{
	int		i;
	int		chk;

	if (trav->cmd[1])
		chk = check_nline_option(trav->cmd);
	else
	{
		ft_putchar_fd('\n', trav->f_out);
		return ;
	}
	i = chk;
	data->chk_dolla = 0;
	while (trav->cmd[i])
	{
		echo_helper(data, trav, i);
		i++;
	}
	if (chk == 1)
		ft_putchar_fd('\n', trav->f_out);
}