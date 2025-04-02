/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:29:22 by aoger             #+#    #+#             */
/*   Updated: 2025/03/14 20:19:41 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "structs.h"

# ifdef __APPLE__

void	rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);
int		rl_on_new_line(void);
void	rl_redisplay(void);
void	add_history(const char *line);
char	*readline(const char *prompt);
# endif

/* TESTS */
// test_init.c
void	ft_test_init(t_data *data);
// test_builtins.c
void	ft_test_builtins(t_data *data);
// test_cmd.c
void	ft_test_cmd(t_data *data);
// test_parsing.c
void	ft_print_tokens(t_token *tokens);
void	ft_print_cmd(t_cmd *cmd);

/* UTILS */
// env_utils.c
char	*ft_getenv(t_env *env, const char *name);
int		ft_setenv(t_env *env, const char *name, const char *value);
// is_smthg.c
int		ft_is_numeric(char *str);
int		ft_is_valid_identifier(char *str);
int		ft_is_builtin(char *cmd);
int		ft_is_shell_space(int c);
// pwd_utils.c
int		ft_update_pwd(t_env *env);
// status_utils.c
int		ft_normalize_status(int status);
// array_utils.c
char	**ft_copy_str_array(char **array, size_t size);
void	ft_sort_str_array(char **array, size_t size);
void	ft_free_array(char **array);
size_t	ft_str_arraylen(void **array);
// std_utils.c
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_charjoin(const char *str, char c);
char	*ft_charjoin_free(char *str, char c);
char	*ft_strjoin_free(char *s1, char *s2);
void	ft_itoa_buffer(int n, char *buffer);

/* CORE */
// init_shell.c
int		ft_init_shell(t_data *data, char **envp);
// shell_loop.c
void	ft_shell_loop(t_data *data);
// signals.c
void	ft_handle_signals(void);
void	ft_handle_signal_status(t_data *data);
void	ft_reset_signals(void);
int		ft_handle_child_signal_status(int status);
// cleanup_shell.c
void	ft_cleanup_shell(t_data *data, t_cmd *cmd);
void	ft_cleanup_heredoc_shell(t_data *data, t_cmd *cmd);
// cleanup_structs.c
void	ft_free_cmd(t_cmd *cmd);
void	ft_free_token_list(t_token *tokens);
void	ft_free_redir_list(t_redir *redir);
void	ft_free_heredoc_redir_list(t_redir *redir);
void	ft_free_token(t_token *token);
// error_print.c
void	ft_print_syntax_error(char *error_token);
int		ft_print_eof_heredoc_warning(char *delimiter, int start_line);
void	ft_print_null_path_error(t_cmd *cmd);

/* PARSING */
// parser.c
t_cmd	*ft_parse_input(char *input, t_data *data);
// tokenizer.c
t_token	*ft_tokenize(char *input, t_data *data);
void	ft_skip_spaces(char *input, size_t *i);
// token_create.c
t_token	*ft_create_token(char *content, int type);
void	ft_add_token(t_token **list, t_token *new);
// token_extract.c
char	*ft_extract_token(char *str, size_t *i);
// token_extract_util.c
int		ft_is_operator(int c);
// token_expand_quotes.c
int		ft_expand_quotes(t_token *token);
int		ft_is_in_quotes(char *str, size_t pos, char quote_type);
int		ft_is_quote(int c);
// token_expand_var.c
int		ft_expand_variables(t_token *token, t_data *data);
// token_expand_utils.c
int		ft_is_in_single_quotes(char *quote_types, int pos);
int		ft_init_quote_removal(char **result, char **quote_types);
int		ft_init_expand_content(char **result, size_t *i, \
size_t *content_len, t_token *current);
int		ft_should_expand(t_token *current, size_t pos);
int		ft_is_dollar_before_quote(t_token *current, size_t pos);
// check_syntax.c
int		ft_check_syntax(t_token *tokens);
// check_syntax_utils.c
char	*ft_get_redir_error_token(t_token *token);
int		ft_check_redirection(t_token *token);
int		ft_is_redirection_token(t_token *token);
// cmd_list_build.c
t_cmd	*ft_build_cmd_list(t_token *tokens, t_data *data);
// cmd_list_utils.c
t_cmd	*ft_init_new_cmd(void);
t_redir	*ft_init_new_redir(void);
void	ft_free_redir(t_redir *redir);
// cmd_list_redirection.c
int		ft_process_redirection(t_cmd *cmd, t_token *token, t_data *data);

/* EXECUTION */
// executor.c
int		ft_execute_cmd(t_cmd *cmd, t_data *data, t_cmd *first);
int		ft_execute_builtin(t_cmd *cmd, t_data *data);
int		ft_execute_external(t_cmd *cmd, t_data *data, t_cmd *first);
// executor_pipeline.c
int		ft_exec_pipeline(t_cmd *cmd, t_data *data, t_cmd *first);
int		ft_execute_cmd_with_args(t_cmd *cmd, t_data *data, t_cmd *first);
void	ft_close_pipes(t_cmd *cmd);
// executor_utils.c
void	ft_close_pipes(t_cmd *cmd);
t_cmd	*ft_find_last_cmd(t_cmd *cmd);
// redirections.c
int		ft_setup_exec_redirections(t_cmd *cmd);
int		ft_has_output_redir(t_cmd *cmd);
// command_finder.c
char	*ft_find_command(char *cmd, t_env *env);
// files_handler.c
int		ft_open_files(t_cmd *cmd);
void	ft_close_files(t_cmd *cmd);
// heredoc_preprocess.c
int		ft_handle_heredoc_preprocessing(t_cmd *cmd, t_cmd *first, t_data *data);
char	*ft_create_heredoc_file(void);
// heredoc_signals.c
int		ft_setup_heredoc_signals(void);
void	ft_handle_heredoc_sigint(int sig);
// heredoc_handler.c
int		ft_handle_heredoc(t_redir *redir);
// fds_handler.c
int		ft_backup_fds(int *stdin_backup, int *stdout_backup);
void	ft_restore_fds(int stdin_backup, int stdout_backup);

/* BUILTINS */
// exit.c
int		ft_exit(t_cmd *cmd, t_data *data);
// env.c
int		ft_env(t_cmd *cmd, t_data *data);
// pwd.c
int		ft_pwd(void);
// cd.c
int		ft_cd(t_cmd *cmd, t_data *data);
// echo.c
int		ft_echo(t_cmd *cmd);
// export.c
int		ft_export(t_cmd *cmd, t_data *data);
// unset.c
int		ft_unset(t_cmd *cmd, t_data *data);

#endif
