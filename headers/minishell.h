/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshatilo <dshatilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/01 16:21:18 by dshatilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"


/*_____ Validate input_____*/
t_bool	validate_input(char *str);
t_bool	validate_and_or(char *str, int *pos);
t_bool	validate_pipeline(char *str, int *pos);
t_bool	validate_command(char *str, int *pos);
t_bool	validate_simple_command(char *str, int *pos);
t_bool	validate_redirect(char *str, int *pos);
t_bool	is_word(char c);

#endif