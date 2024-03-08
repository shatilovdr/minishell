/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnikifor <dnikifor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:06 by dshatilo          #+#    #+#             */
/*   Updated: 2024/03/08 17:26:22 by dnikifor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include "defines.h"

#include <stdio.h>

# include <readline/readline.h>
# include <readline/history.h>

t_and			*init_t_and(void);
t_or			*init_t_or(void);
t_pipe			*init_t_pipe(void);
t_bracket		*init_t_bracket(void);
t_command		*init_t_command(void);
t_command_br	*init_t_command_br(void);
t_cmd_simple	*init_t_cmd_simple(void);
t_redir			*init_t_redir(void);

t_bool			create_tree(char *str, t_node **root);
t_bool			create_node(t_node_data *data, t_node **base);
void			free_node_data(t_node_data *data);
void			free_tree(t_node **root);

t_bool			add_and_or_pipe_trees(t_node_data *data, t_node **root);
t_bool			add_bracket(t_node_data *data, t_node **root);
t_bool			add_command(t_node_data *data, t_node **root);
t_bool			add_command_br(t_node_data *data, t_node **root);
t_bool			add_cmd_simple(t_node_data *data, t_node **root);

//validator

t_bool			tree_validation(char *str);
t_bool			pre_validataion(char *str);
void			remove_quotes(char *str, int i, int j);
int				check_if_round_brackets_num_is_even(char *str, int key,
					int quote_type);
int				check_if_quotes_num_is_even(char *str, int i, int counter);
int				round_brackets_without_args_check(char *str, int key,
					int quote_type);
int				check_if_redirect_file_pattern_complied_sequel(char *str,
					int i);
int				round_brackets_with_args_check(char *str, int key,
					int quote_type);
int				check_if_file_pattern_complied(char *str, int quote_type,
					int i);
int				one_and_symbol_check(char *str, int quote_type, int i);
int				check_if_redirects_are_correct(char *str, int quote_type);
int				check_if_redirects_without_nl(char *str);
void			check_if_inside_quotes(char *str, int *i,
					int *quote_type);
int				check_if_backslash_or_semicolon_exist(char *str,
					int quote_type);

//ast_string_splitter

t_bool			get_type(char *str, t_node_data **data);
int				set_node_data_and_or_pipe(t_node_data **node, char *str,
					int point, int type);
int				set_node_data_command_br(t_node_data **node, char *str,
					int type);
int				set_node_data_command(t_node_data **node, char *str, int type);
int				set_node_data_bracket(t_node_data **node, char *str, int type);
int				set_node_cmd_simple(t_node_data **node, char *str, int type);
int				and_if_condition_block(t_node_data **node, char *str, int type,
					int i);
int				string_splitter(t_node_data **node, char *str, int type,
					int i);
t_bool			if_odd(int number);
int				round_brackets_check(char *str, int point);
int				quote_check(char *str, int point, int symbol);
int				first_nonspace_char_is_bracket(char *str);
int				last_nonspace_char_is_bracket(char *str);
char			*command_part(char *str, int *i, int quote_type);
int				modificate_str_command_without_br(char *str, char **redir,
					int i, int j);
int				and_if_condition_block(t_node_data **node, char *str, int type,
					int i);
int				pipe_block(t_node_data **node, char *str, int type, int i);
int				brackets_block(t_node_data **node, char *str, int type);
int				command_block(t_node_data **node, char *str, int type);
int				command_without_bracket_block(t_node_data **node, char *str,
					int type);
int				brackets_search(char *str);
int				redir_search(char *str);

// errors

void			error_processing(char *str, int type, int key);
void			brackets_syntax_error_handler(char *str, int i, int j,
					int quote_type);
void			bracket_error_handler(int key);
void			quotes_error_handler(int key);
void			brackets_args_syntax_error_handler(char *str, int i, int j,
					int quote_type);
void			meta_syntax_error_handler(char *str, int i);
void			meta_pattern_error_handler(char *str, int i);
void			meta_nl_error_handler(void);
void			extra_characters_error_handler(int key);
void			error_print(char *str);

// builtins

// common + utils
int				command_run(char **arr, char ***envp);
char			**sort_string_arr(char **argv, int size);
char			**cpy_env(char **envp);
void			remove_quotes(char *str, int i, int j);
void			skip_characters(char *str, int *i, int symbol);
void			processing(char **arr, int i);
int				env_var(char **envp, char *var, int i, int j);
int				arg_var(char **arr, char *var, int i, int j);
t_bool			ft_isenv(char c, int *j);

//errors_print
void			print_error_with_arg(char *error, char *arg, char *cmd);
void			print_error(char *error, char *cmd);

//cd
int				run_cd(char **arr, char **envp);

//echo
int				run_echo(char **arr, int i, int j, int nl_flag);

//export
int				run_export(char **arr, char ***envp);
void			create_operations_array(char **arr, char **envp,
					int *operations);
int				check_operations(int *operations, int *i, int *j, int type);
void			execute_error(char **arr, int *operations);
int				edit_env_list(char ***new_env, char **arr, int *operations);
int				add_to_env_list(char ***new_env, char **arr, char **envp,
					int *operations);

//pwd
int				run_pwd(char **arr);

//unset
int				run_unset(char **arr, char ***envp);

//env
int				run_env(char **arr, char ***envp);

int				dollar_sign_expansion(char **arr, char **envp);

#endif