# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 17:08:53 by ndelhota          #+#    #+#              #
#    Updated: 2025/03/17 16:00:57 by ndelhota         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell 

SRC := main.c \
       gen/ft_gen.c \
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
       end/ft_end.c \
       end/ft_end_list.c \

CC := cc

CFLAGS := -g -Wall -Werror -Wextra

OBJ := $(SRC:.c=.o)


LIB := lib/libft/libft.a \

all : $(LIB) $(OBJ) $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) -lreadline

$(LIB) :
	make -C lib/libft

clean :
	rm -f $(OBJ) 
	make -C lib/libft clean

fclean : clean 
	rm -f $(NAME)
	make -C lib/libft fclean

re : fclean all

.PHONY : all clean fclean re
.PHONY : all clean fclean re
