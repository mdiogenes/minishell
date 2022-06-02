# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 22:26:19 by mporras-          #+#    #+#              #
#    Updated: 2022/06/01 10:24:55 by msoler-e         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES		=	aaa_debug.c \
					cmd_cd.c \
					cmd_env.c \
					exe_forks.c \
					exe_pipes.c \
					exp_export_utl.c \
					exp_list.c \
					main.c \
					ms_error_handler.c \
					ms_process.c \
					ms_expand.c \
					ms_signals.c \
					ms_string_utils.c \
					ms_struct_utils.c \
					msg_child_signals.c \
					rdr_functions.c \
					rdr_heredoc.c \
					utl_cleaning.c \
					utl_list.c \
					cmd/cmd_echo.c \
					cmd/cmd_exit.c \
					cmd/cmd_ls.c \
					inp/inp_directory.c \
					inp/inp_workflow.c \
					inp/inp_input.c \
					inp/inp_export.c \
					inp/inp_input_checks.c
SRCS_DIR		=	srcs
OBJS_DIR		=	obj
SRCS 			=	$(addprefix $(SRCS_DIR)/,$(SRCS_FILES))
OBJS			=	$(addprefix $(OBJS_DIR)/,$(SRCS_FILES:.c=.o))
LIB_DIR			=	lib
LIB 			=	libft.a
LEAKS			=	valgrind --leak-check=full --track-fds=yes --trace-children=yes -s -q
CC				=	gcc
RM				= 	rm -f
CFLAGS			=	-Wall -Wextra -Werror
INCLUDES		=	-Iinc -Ilib
INC_READLINE	=	/Users/${USER}/.brew/opt/readline/include/
LIB_READLINE	=	/Users/${USER}/.brew/opt/readline/lib
#manuel readline
#INC_READLINE	=	/usr/local/opt/readline/include
#LIB_READLINE	=	/usr/local/opt/readline/lib
HEADER			=	minishell.h
HEADER_DIR		=	inc
NAME			=	minishell


all: libs $(NAME) $(HEADER_DIR)/$(HEADER)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIB_DIR)/$(LIB) $(CFLAGS) -L$(LIB_READLINE) -lreadline -o $(NAME)

libs: 
	@$(MAKE) -C ./$(LIB_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LIB_DIR)/inc -I$(HEADER_DIR) -I$(INC_READLINE) -c $< -o $@

clean:
	$(MAKE) -C ./$(LIB_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C ./$(LIB_DIR) fclean
	$(RM) $(NAME)

leak: all
	$(LEAKS) ./$(NAME)

re:	fclean libs $(NAME)

.PHONY: all clean fclean re leak
