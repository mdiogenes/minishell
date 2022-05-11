# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 22:26:19 by mporras-          #+#    #+#              #
#    Updated: 2022/05/11 12:28:23 by msoler-e         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
SRC_DIR			=	srcs
SRCS_FILES		=	cmd_cd.c \
					cmd_directory.c \
					cmd_ls.c \
					cmd_echo.c \
					main.c \
					ms_error_handler.c \
					ms_input.c \
					ms_signals.c \
					ms_string_utils.c \
					ms_struct_utils.c
SRCS 			=	$(addprefix $(SRC_DIR)/,$(SRCS_FILES))
OBJS			=	$(SRCS_FILES:.c=.o)
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
HEADERe			=	minishell.h
HEADER_DIR		=	inc

all: libs $(NAME)

$(NAME): $(OBJS) $(HEADER_DIR)/$(HEADERe)
	$(CC) $(OBJS) $(CFLAGS) -Llib -lft -L$(LIB_READLINE) -lreadline -o $(NAME)

libs: 
	@$(MAKE) -C ./$(LIB_DIR)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -I$(HEADER_DIR) -I$(INC_READLINE) -c $(SRCS)

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
