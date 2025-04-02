NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

MAKEFLAGS += --no-print-directory

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
RESET = \033[0m

# MacOS
ifeq ($(shell uname), Darwin)
	READLINE_DIR = $(shell brew --prefix readline)
	CFLAGS += -I$(READLINE_DIR)/include
	LDFLAGS = -L$(READLINE_DIR)/lib
endif

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
G_LIBFT_DIR = g_libft

# Sources
SRC_TESTS =		$(SRC_DIR)/tests/test_init.c \
				$(SRC_DIR)/tests/test_builtins.c \
				$(SRC_DIR)/tests/test_cmd.c \
				$(SRC_DIR)/tests/test_parsing.c
SRC_UTILS =		$(SRC_DIR)/utils/is_smthg.c \
				$(SRC_DIR)/utils/env_utils.c \
				$(SRC_DIR)/utils/pwd_utils.c \
				$(SRC_DIR)/utils/status_utils.c \
				$(SRC_DIR)/utils/array_utils.c \
				$(SRC_DIR)/utils/std_utils.c
SRC_CORE =		$(SRC_DIR)/core/shell_loop.c \
				$(SRC_DIR)/core/init_shell.c \
				$(SRC_DIR)/core/signals.c \
				$(SRC_DIR)/core/cleanup_shell.c \
				$(SRC_DIR)/core/cleanup_structs.c \
				$(SRC_DIR)/core/error_print.c
SRC_PARSING =	$(SRC_DIR)/parsing/parser.c \
				$(SRC_DIR)/parsing/token_create.c \
				$(SRC_DIR)/parsing/tokenizer.c \
				$(SRC_DIR)/parsing/token_extract.c \
				$(SRC_DIR)/parsing/token_extract_utils.c \
				$(SRC_DIR)/parsing/token_expand_quotes.c \
				$(SRC_DIR)/parsing/token_expand_var.c \
				$(SRC_DIR)/parsing/token_expand_utils.c \
				$(SRC_DIR)/parsing/check_syntax.c \
				$(SRC_DIR)/parsing/check_syntax_utils.c \
				$(SRC_DIR)/parsing/cmd_list_build.c \
				$(SRC_DIR)/parsing/cmd_list_utils.c \
				$(SRC_DIR)/parsing/cmd_list_redirection.c
SRC_EXECUTION =	$(SRC_DIR)/execution/executor.c \
				$(SRC_DIR)/execution/executor_pipeline.c \
				$(SRC_DIR)/execution/executor_utils.c \
				$(SRC_DIR)/execution/redirections.c \
				$(SRC_DIR)/execution/command_finder.c \
				$(SRC_DIR)/execution/files_handler.c \
				$(SRC_DIR)/execution/heredoc_handler.c \
				$(SRC_DIR)/execution/heredoc_preprocess.c \
				$(SRC_DIR)/execution/heredoc_signals.c \
				$(SRC_DIR)/execution/fds_handler.c
SRC_BUILTINS =	$(SRC_DIR)/builtins/cd.c \
				$(SRC_DIR)/builtins/echo.c \
				$(SRC_DIR)/builtins/env.c \
				$(SRC_DIR)/builtins/exit.c \
				$(SRC_DIR)/builtins/export.c \
				$(SRC_DIR)/builtins/pwd.c \
				$(SRC_DIR)/builtins/unset.c

SRC =	$(SRC_DIR)/main.c \
		$(SRC_TESTS) \
		$(SRC_UTILS) \
		$(SRC_CORE) \
		$(SRC_PARSING) \
		$(SRC_EXECUTION) \
		$(SRC_BUILTINS)

BONUS_SRC =	$(SRC_DIR)/parsing/ast_builder_bonus.c \
			$(SRC_DIR)/parsing/ast_builder_utils_bonus.c \
			$(SRC_DIR)/parsing/ast_process_bonus.c \
			$(SRC_DIR)/parsing/ast_utils_bonus.c \
			$(SRC_DIR)/parsing/check_syntax_bonus.c \
			$(SRC_DIR)/execution/ast_executor_bonus.c \
			$(SRC_DIR)/utils/utils_bonus.c \
			$(SRC_DIR)/tests/test_ast_bonus.c \
			$(SRC_DIR)/parsing/wildcards_expand_bonus.c \
			$(SRC_DIR)/execution/files_wildcards_handler_bonus.c

RECOMPILE_FOR_BONUS =	$(SRC_DIR)/core/shell_loop.c \
						$(SRC_DIR)/parsing/parser.c \
						$(SRC_DIR)/parsing/tokenizer.c \
						$(SRC_DIR)/parsing/check_syntax.c \
						$(SRC_DIR)/execution/files_handler.c

# Objects
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJ = $(BONUS_SRC:%.c=$(OBJ_DIR)/%.o)
RECOMPILE_OBJ = $(RECOMPILE_FOR_BONUS:%.c=$(OBJ_DIR)/%.o)

BONUS_FLAG = $(OBJ_DIR)/.bonus_compiled

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)/$(dir $<)
	@echo "$(BLUE)Compiling:$(RESET) $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

ifdef WITH_BONUS
OBJ_LIST = $(OBJ) $(BONUS_OBJ)
else
OBJ_LIST = $(OBJ)
endif

# Libraries
LIBFT = $(G_LIBFT_DIR)/libft.a
LIBS = -L$(G_LIBFT_DIR) -lft -lreadline

# Headers
INCLUDES =	-I$(INC_DIR) \
			-I$(G_LIBFT_DIR)/ft_std \
			-I$(G_LIBFT_DIR)/ft_printf \
			-I$(G_LIBFT_DIR)/get_next_line

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(G_LIBFT_DIR)

$(NAME): $(OBJ_LIST)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJ_LIST) $(LDFLAGS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) is ready!$(RESET)"

bonus: $(BONUS_FLAG)
	@echo "$(MAGENTA)Compiling with bonus features...$(RESET)"
	@make WITH_BONUS=1 CFLAGS="$(CFLAGS) -D ENABLE_BONUS" all

$(BONUS_FLAG):
	@mkdir -p $(OBJ_DIR)
	@rm -f $(RECOMPILE_OBJ)
	@touch $(BONUS_FLAG)

# Clean
clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@make clean -C $(G_LIBFT_DIR)
	@echo "Cleaning minishell object files..."
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Clean complete!$(RESET)"

fclean:
	@echo "$(YELLOW)Full cleaning...$(RESET)"
	@make fclean -C $(G_LIBFT_DIR)
	@echo "Cleaning minishell object files..."
	@rm -rf $(OBJ_DIR)
	@echo "Removing minishell executable..."
	@rm -f $(NAME)
	@echo "$(GREEN)Full clean complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
