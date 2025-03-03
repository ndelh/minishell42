# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndelhota <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/10 17:08:53 by ndelhota          #+#    #+#              #
#    Updated: 2025/03/03 15:10:25 by ndelhota         ###   ########.fr        #
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
       tokenize/split_redir.c \
       tokenize/third_sort.c \
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
