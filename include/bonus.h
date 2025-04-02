/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:42:15 by aoger             #+#    #+#             */
/*   Updated: 2025/03/15 00:45:54 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include <dirent.h>

# include "structs.h"

# define TOKEN_OR 8
# define TOKEN_AND 9
# define TOKEN_LPARENTH 10
# define TOKEN_RPARENTH 11

# define PRIO_LOGIC_OP 0
# define PRIO_PIPE 1
# define PRIO_GRP_AND_CMD 2

# define AST_OR 10
# define AST_AND 11
# define AST_PIPE 12
# define AST_GROUP 13
# define AST_CMD 14

typedef struct s_ast
{
	int				type;
	struct s_ast	*left;
	struct s_ast	*right;
	t_token			*cmd_tokens;
	t_cmd			*cmd;
}	t_ast;

// PROTOTYPES

// TESTS
// test_ast_bonus.c
void	ft_print_ast(t_ast *ast);

// UTILS
// utils_bonus.c
int		ft_has_logical_operators(char *input);
int		ft_is_ast_op(char c, char next_c);
int		ft_has_wildcards(const char *str);
int		ft_insert_strs_in_array(char ***array, char **strs, int strs_count, \
size_t insert_pos);
char	**ft_add_str_after_array(char **array, size_t *size, char *new_str);

// PARSING
// ast_parser_bonus.c
t_ast	*ft_ast_parse_input(char *input, t_data *data);
// check_syntax_bonus.c 
int		ft_check_parentheses_balance(t_token *token);
int		ft_is_operator_token(t_token *token);
int		ft_is_parenth_token(t_token *token);
// ast_builder_bonus.c
t_ast	*ft_build_ast(t_token **token, int priority);
// ast_builder_utils_bonus.c
t_ast	*ft_create_op_node(t_ast *left, int op_type);
int		ft_is_token_operator(t_token *token);
t_token	*ft_token_dup(t_token *token);
// ast_utils_bonus.c
t_ast	*ft_init_new_ast(void);
void	ft_free_ast_node(t_ast *ast_node);
// ast_process_bonus.c
int		ft_process_ast(t_ast *ast_node, t_data *data);
// wildcard_expand_bonus.c
int		ft_expand_cmd_wildcards(t_cmd *cmd);
char	**ft_expand_wildcards(const char *pattern);

// EXECUTION
// ast_executor_bonus.c
int		ft_execute_ast(t_ast *ast_node, t_data *data);
// files_wildcards_handler_bonus.c
int		ft_handle_redirection_wildcards(t_redir *redir);

#endif