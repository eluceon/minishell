NONE = \033[0;0m
RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[0;35m

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

LIBFT = ./libs/libft/libft.a
LIBFTDIR = ./libs/libft/

NAME = minishell

OBJDIR = ./obj/
HEADERDIR = ./includes/

SRC_MAIN_DIR = ./srcs/main/
SRCS_MAIN = minishell.c history.c executor.c
OBJ_MAIN = $(addprefix $(OBJDIR), $(SRCS_MAIN:.c=.o))
HEADER_MAIN = $(addprefix $(HEADERDIR), minishell.h)

SRC_SIGNAL_HANDLERS_DIR = ./srcs/signal_handlers/
SRCS_SIGNAL_HANDLERS = signal_handlers.c
OBJ_SIGNAL_HANDLERS = $(addprefix $(OBJDIR), $(SRCS_SIGNAL_HANDLERS:.c=.o))
HEADER_SIGNAL_HANDLERS = $(addprefix $(HEADERDIR), signal_handlers.h)

SRC_ENVIRONMENT_DIR = ./srcs/environment/
SRCS_ENVIRONMENT = set_environment.c change_environment.c
OBJ_ENVIRONMENT = $(addprefix $(OBJDIR), $(SRCS_ENVIRONMENT:.c=.o))
HEADER_ENVIRONMENT = $(addprefix $(HEADERDIR), environment.h)

SRC_UTILS_DIR = ./srcs/utils/
SRCS_UTILS = ft_realloc.c ft_malloc.c ft_crash.c\
			ft_iswhitespace.c str_join_char.c free_all_exit.c doubly_lst_new.c\
			doubly_lst_last.c doubly_lst_append.c doubly_lst_clear.c\
			special_symbols.c doubly_lst_delete_element.c doubly_lst_dup.c\
			doubly_lst_merge_sort.c other.c is_number.c doubly_lst_size.c fd.c \
			my_putchar.c is_valid_variable_name.c ft_str_replace.c \
			doubly_lst_split.c print_promt.c check_history_i.c

OBJ_UTILS = $(addprefix $(OBJDIR), $(SRCS_UTILS:.c=.o))
HEADER_UTILS = $(addprefix $(HEADERDIR), utils.h)

SRC_TERMCAP_COMMANDS_DIR = ./srcs/termcap_commands/
SRCS_TERMCAP_COMMANDS = termcap_commands.c handle_key_manage.c ctrl_key_manage.c\
						handle_key_manage2.c
OBJ_TERMCAP_COMMANDS = $(addprefix $(OBJDIR), $(SRCS_TERMCAP_COMMANDS:.c=.o))
HEADER_TERMCAP_COMMANDS = $(addprefix $(HEADERDIR), termcap_commands.h)

SRC_PARSING_DIR = ./srcs/parsing/
SRCS_PARSING = read_line.c parsing.c quote_handler.c handle_special_chars.c\
			double_quotes.c operator_handler.c
OBJ_PARSING = $(addprefix $(OBJDIR), $(SRCS_PARSING:.c=.o))
HEADER_PARSING = $(addprefix $(HEADERDIR), parsing.h)

SRC_BUILTINS_DIR = ./srcs/builtins/
SRCS_BUILTINS = builtins.c cd.c echo.c env.c pwd.c unset.c export.c exit.c
OBJ_BUILTINS = $(addprefix $(OBJDIR), $(SRCS_BUILTINS:.c=.o))
HEADER_BUILTINS = $(addprefix $(HEADERDIR), builtins.h)

SRC_ERROR_HANDLERS_DIR = ./srcs/error_handlers/
SRCS_ERROR_HANDLERS = error_handlers.c error_messages.c
OBJ_ERROR_HANDLERS = $(addprefix $(OBJDIR),\
								$(SRCS_ERROR_HANDLERS:.c=.o))
HEADER_ERROR_HANDLERS = $(addprefix $(HEADERDIR), error_handlers.h)

SRC_EXEC_COMMANDS_DIR = ./srcs/exec_commands/
SRCS_EXEC_COMMANDS = exec_commands.c make_arrrays.c find_path.c redirects.c\
					variable_heredoc.c
OBJ_EXEC_COMMANDS = $(addprefix $(OBJDIR), $(SRCS_EXEC_COMMANDS:.c=.o))
HEADER_EXEC_COMMANDS = $(addprefix $(HEADERDIR), exec_commands.h)


OBJ_ALL = $(OBJ_MAIN) $(OBJ_SIGNAL_HANDLERS) $(OBJ_ENVIRONMENT) $(OBJ_UTILS)\
		$(OBJ_ERROR_HANDLERS) $(OBJ_PARSING) $(OBJ_TERMCAP_COMMANDS)\
		$(OBJ_BUILTINS) $(OBJ_EXEC_COMMANDS)

all: make_libft $(NAME)

make_libft:
	$(MAKE) -C $(LIBFTDIR)


$(NAME): $(OBJDIR) $(OBJ_ALL)
	$(CC) $(CFLAGS) $(OBJ_ALL) -ltermcap $(LIBFT) -o $@
	@echo "$(PURPLE) $(NAME) has been created $(NONE)"

$(OBJDIR):
	mkdir -p $(OBJDIR)

##########################
##   Main compilation   ##
##########################

$(OBJ_MAIN): $(OBJDIR)%.o: $(SRC_MAIN_DIR)%.c $(HEADER_MAIN) $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(LIBFTDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN)for Main has been created $(NONE)"

###################################
##    Environment compilation    ##
###################################

$(OBJ_ENVIRONMENT): $(OBJDIR)%.o: $(SRC_ENVIRONMENT_DIR)%.c\
					 $(HEADER_ENVIRONMENT) $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(LIBFTDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for Environment has been created $(NONE)"

###############################
##    Parsing compilation    ##
###############################

$(OBJ_PARSING): $(OBJDIR)%.o: $(SRC_PARSING_DIR)%.c\
					 $(HEADER_PARSING) $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(LIBFTDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for Parsing has been created $(NONE)"

#######################################
##    Signal handlers compilation    ##
#######################################

$(OBJ_SIGNAL_HANDLERS): $(OBJDIR)%.o: $(SRC_SIGNAL_HANDLERS_DIR)%.c $(HEADER_SIGNAL_HANDLERS) $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(LIBFTDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for Signal handlers has been created $(NONE)"

###############################
##     Utils compilation     ##
###############################

$(OBJ_UTILS): $(OBJDIR)%.o: $(SRC_UTILS_DIR)%.c $(HEADER_UTILS) $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(LIBFTDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for Utils has been created $(NONE)"

########################################
##    termcap_commands compilation    ##
########################################

$(OBJ_TERMCAP_COMMANDS): $(OBJDIR)%.o: $(SRC_TERMCAP_COMMANDS_DIR)%.c\
						$(HEADER_TERMCAP_COMMANDS) $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(LIBFTDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN)for termcap_commands has been created $(NONE)"

#####################################
##   error_handlers compilation    ##
#####################################

$(OBJ_ERROR_HANDLERS): $(OBJDIR)%.o: $(SRC_ERROR_HANDLERS_DIR)%.c $(HEADER_ERROR_HANDLERS) $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(LIBFTDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN) for error_handlers has been created $(NONE)"

###############################
##   builtins compilation    ##
###############################

$(OBJ_BUILTINS): $(OBJDIR)%.o: $(SRC_BUILTINS_DIR)%.c $(HEADER_BUILTINS)\
	$(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(LIBFTDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@ $(GREEN) for builtins has been created $(NONE)"


###################################
##   exec_commands compilation   ##
###################################

$(OBJ_EXEC_COMMANDS): $(OBJDIR)%.o: $(SRC_EXEC_COMMANDS_DIR)%.c\
	$(HEADER_EXEC_COMMANDS) $(LIBFT)
	$(CC) $(CFLAGS) -I$(HEADERDIR) -I$(LIBFTDIR) -c $< -o $@
	@echo "$(GREEN) Object file $(PURPLE)$@$(GREEN) for exec commands has been created $(NONE)"


clean:
	$(MAKE)	clean -C $(LIBFTDIR)
	$(RM) $(OBJDIR)
	@echo "$(RED) $(OBJDIR) has been deleted $(NONE)"

fclean: clean
	$(MAKE)	fclean -C $(LIBFTDIR)
	$(RM) $(NAME) minishell_history
	@echo "$(RED) $(NAME) has been deleted $(NONE)"

re:	fclean all

.PHONY: all clean fclean re
