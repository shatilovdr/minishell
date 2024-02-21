/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_meta.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:34:13 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/19 18:55:08 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
* auxiliary function for the check_if_redirect_file_pattern_complied()
*
* Input:
* - `str` - string that coming from readline function
* - `i` - iteration index
* 
* Output:
* - `0` (VALID) or `1` (INVALID)
*/
static int	check_if_redirect_file_pattern_complied_sequel(char *str, int i)
{
	while (str[i] == SPACE && str[i] != NULL_TERM)
		i++;
	if (str[i] == REDIR_R || str[i] == REDIR_L || str[i] == NULL_TERM)
		return (INVALID);
	return (VALID);
}

/*
* Function that checks if redirection pattern is followed:
* `> | < | >> | << file`
*
* Input:
* - `str` - string that coming from readline function
* - `quote_type` - int that tracks if we are within a quotes or not
* - `i` - iteration index
* 
* Output:
* - `0` (VALID) or `1` (INVALID)
*/
int	check_if_redirect_file_pattern_complied(char *str, int quote_type, int i)
{
	while (str[i] != NULL_TERM)
	{
		check_if_inside_quotes_with_incr(str, &i, &quote_type);
		if (!quote_type)
		{
			if ((str[i] == REDIR_R && str[i + 1] != REDIR_R)
				|| (str[i] == REDIR_L && str[i + 1] != REDIR_L))
			{
				if (check_if_redirect_file_pattern_complied_sequel(str, i + 1))
					return (INVALID);
			}
			else if ((str[i] == REDIR_R && str[i + 1] == REDIR_R)
				|| (str[i] == REDIR_L && str[i + 1] == REDIR_L))
			{
				if (check_if_redirect_file_pattern_complied_sequel(str, i + 2))
					return (INVALID);
				i++;
			}
			i++;
		}
		else
			i++;
	}
	return (VALID);
}

/*
* Function that checks if redirections, &&, || are written in a proper way
*
* Input:
* - `str` - string that coming from readline function
* - `first` - first meta character
* - `second` - second meta character
* - `quote_type` - int that tracks if we are within a quotes or not
* 
* Output:
* - `0` (VALID) or `1` (INVALID)
*/
int	check_if_redirects_and_or_are_correct(char *str, int first,
	int second, int quote_type)
{
	int	i;

	i = 0;
	while (str[i] != NULL_TERM)
	{
		check_if_inside_quotes_with_incr(str, &i, &quote_type);
		if (!quote_type)
		{
			if ((str[i] == first && str[i + 1] == second)
				|| (str[i] == second && str[i + 1] == first))
				return (INVALID);
			if ((str[i] == second && str[i + 1] == second)
				|| (str[i] == first && str[i + 1] == first))
			{
				if (str[i + 2] == second || str[i + 2] == first)
					return (INVALID);
			}
			i++;
		}
		else
			i++;
	}
	return (VALID);
}
