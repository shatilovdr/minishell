/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:43:09 by dnikifor          #+#    #+#             */
/*   Updated: 2024/02/22 22:41:33 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
* Auxiliary function that checks if we are inside of the quotes
*
* Input:
* - `str` - string that coming from readline function
* - `i` - pointer to the index to increment
* - `quote_type` - pointer to the int that tracks if we are within the quotes
* or not
* 
*/
void	check_if_inside_quotes(char *str, int *i, int *quote_type)
{
	if (str[*i] == S_QUOTE && *quote_type == S_QUOTE)
		*quote_type = 0;
	else if (str[*i] == S_QUOTE && *quote_type == 0)
		*quote_type = S_QUOTE;
	else if (str[*i] == D_QUOTE && *quote_type == D_QUOTE)
		*quote_type = 0;
	else if (str[*i] == D_QUOTE && *quote_type == 0)
		*quote_type = D_QUOTE;
}

/*
* Function that checks if there are any semicolons or backslashes outside
* of the quotes
*
* Input:
* - `str` - string that coming from readline function
* - `quote_type` - pointer to the int that tracks if we are within the quotes
* or not
* 
* Output:
* - `0` (VALID) or `1` (INVALID)
*/
int	check_if_backslash_or_semicolon_exist(char *str, int quote_type)
{
	int	i;

	i = 0;
	while (str[i] != NULL_TERM)
	{
		check_if_inside_quotes(str, &i, &quote_type);
		if (!quote_type)
		{
			if (str[i] == SEMICOLON || str[i] == BACKSLASH)
				return (INVALID);
			i++;
		}
		else
			i++;
	}
	return (VALID);
}
