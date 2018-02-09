# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pzubar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/02 22:26:16 by pzubar            #+#    #+#              #
#    Updated: 2018/02/02 22:26:20 by pzubar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC = ft_printf_algo.c ft_printf_comp.c ft_printf_help.c ft_printf_nums.c\
	ft_printf_parse.c ft_printf_strs.c
OBJ =  $(SRC:.c=.o)

%.o: %.c
	@gcc -c $? -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@ar rc $(NAME) libft/*.o *.o
	@echo "The \"libftprintf.a\" is ready to use"

clean:
	@/bin/rm -f *.o
	@/bin/rm -f libft/*.o
	@echo "Object files were successfully removed"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "The \"libftprintf.a\" was successfully removed"

re: fclean all
	@echo "The project was successfully recompiled"