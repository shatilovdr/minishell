/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 22:24:56 by dshatilo          #+#    #+#             */
/*   Updated: 2024/04/05 11:42:39 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	apply_redirect(char *redir, t_minishell *ms, int *in, int *out);
int	replace_fd(int in, int out);

int	apply_redirects(char *redir, t_minishell *ms)
{
	char	**redirs;
	int		i;
	int		status;
	int		in;
	int		out;

	in = -1;
	out = -1;
	redirs = ft_split(redir, SEPARATOR);
	if (!redirs)
		return (MALLOC_ERR);
	status = 0;
	i = 0;
	while (redirs[i] && status == 0)
	{
		status = apply_redirect(redirs[i], ms, &in, &out);
		i++;
	}
	ft_free_2d_array(redirs);
	if (status == 0)
		status = replace_fd(in, out);
	return (status);
}

int	apply_redirect(char *redir, t_minishell *ms, int *in, int *out)
{
	int	status;
	status = 0;

	if (ft_strncmp(redir, "<<", 2) == 0)
		status = apply_heredoc(redir + 2, in);
	if (ft_strncmp(redir, ">>", 2) == 0)
		status = apply_apend(redir + 2, ms, out);
	else if (ft_strncmp(redir, "<", 1) == 0)
		status = apply_redir_in(redir + 1, ms, in);
	if (ft_strncmp(redir, ">", 1) == 0)
		status = apply_redir_out(redir + 1, ms, out);
	return (status);
}

int	replace_fd(int in, int out)
{
	int	status;

	status = 0;
	if (in != -1)
	{
		status = dup2(in, STDIN_FILENO);
		close(in);
	}
	if (status == 0 && out != -1)
	{
		status = dup2(out, STDOUT_FILENO);
		close(out);
	}
	return (status);
}
