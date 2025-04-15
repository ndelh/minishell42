# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 17:08:53 by ndelhota          #+#    #+#              #
#    Updated: 2025/04/15 17:53:07 by ndelhota         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell 

SRC := main.c \
       gen/ft_gen.c \
       gen/ft_dup_std.c\
       gen/convert_list_to_envp.c \
       gen/mns_sig_init.c \
       tokenizer/tokenize.c \
       tokenizer/gen_list.c \
       tokenizer/quoting.c \
       tokenizer/piping.c \
       tokenizer/redirecting.c \
       tokenizer/sorting_by_cmd.c \
       tokenizer/sorting_in_cmd.c \
       tokenizer/convert_redir.c \
       tokenizer/convert_cmd.c \
       tokenizer/tokenize_end.c \
       tokenizer/tokenize_utils.c \
       tokenizer/gen_expand.c \
       tokenizer/redir_utils.c \
       tokenizer/create_here_doc.c \
       tokenizer/here_doc_utils.c \
       tokenizer/expand_utils.c \
       tokenizer/expand_in_redir.c \
       tokenizer/is_builtin.c \
       utils/tab_utils.c \
       utils/list_utils.c \
       utils/prompt.c \
       builtin/mns_export01.c \
       builtin/mns_export02.c \
       builtin/unset.c \
       builtin/mns_env.c \
       builtin/mns_exit.c \
       builtin/mns_echo.c \
       builtin/cd.c \
       builtin/pwd.c \
       builtin/mns_mns.c \
       end/ft_end.c \
       end/ft_end_list.c \
       utils/mns_utils01.c \
       utils/mns_lstfct01.c \
       utils/mns_error01.c \
       utils/split_w_space.c \
       utils/space_strchr.c \
       exec/mns_exec01.c \
       exec/mns_exec02.c

CC := cc

CFLAGS := -g -Wall -Werror -Wextra

OBJDIR = obj
OBJ = $(SRC:.c=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))

LIB := lib/libft/libft.a \

all : $(LIB) $(OBJ) $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) -lreadline

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c -o $@ $^

$(LIB) :
	@make bonus -C lib/libft

clean :
	@rm -rf $(OBJDIR) 
	@make -C lib/libft clean

fclean : clean 
	@rm -f $(NAME)
	@make -C lib/libft fclean

re : fclean all

.PHONY : all clean fclean re
