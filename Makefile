# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 17:08:53 by ndelhota          #+#    #+#              #
#    Updated: 2025/03/20 10:12:17 by ndelhota         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell 

SRC := main.c \
       gen/ft_gen.c \
       gen/ft_dup_std.c\
       gen/convert_list_to_envp.c \
       tokenize/begin.c \
       tokenize/ft_split_quote.c \
       tokenize/first_sort.c \
       tokenize/second_sort.c \
       tokenize/split_pipe.c \
       tokenize/separate_cmd.c \
       tokenize/split_redir.c \
       tokenize/third_sort.c \
       tokenize/seek_block_utils.c \
       tokenize/seek_block.c \
       tokenize/seek_block_tail.c \
       tokenize/isolate_redir.c \
       tokenize/expand.c \
       tokenize/gen_expand.c \
       tokenize/expand_utils.c \
       tokenize/complex_line.c \
       tokenize/convert_list.c \
       tokenize/convert_redir_list.c \
       tokenize/tokenize_utils.c \
       tokenize/create_here_doc.c \
       utils/tab_utils.c \
       utils/list_utils.c \
       builtin/unset.c \
       end/ft_end.c \
       end/ft_end_list.c \
       utils/mns_utils01.c \
       utils/mns_lstfct01.c \
       utils/mns_error01.c \
       gen/mns_sig_init.c \
       exec/mns_exec01.c \
       exec/mns_exec02.c \
       builtin/mns_export.c

CC := cc

CFLAGS := -g -Wall -Werror -Wextra

OBJDIR = obj
OBJ = $(SRC:.c=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))

LIB := lib/libft/libft.a \

all : $(LIB) $(OBJ) $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) -lreadline

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
