# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pzubar <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/01 22:19:39 by pzubar            #+#    #+#              #
#    Updated: 2017/11/10 16:17:18 by pzubar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_atoi.c ft_strcpy.c ft_strdup.c ft_strlen.c ft_isdigit.c ft_strcat.c ft_strcmp.c ft_isalnum.c\
	ft_isalpha.c ft_isascii.c ft_isprint.c ft_tolower.c ft_toupper.c ft_memset.c ft_bzero.c ft_strncpy.c\
	ft_memmove.c ft_memchr.c ft_memcpy.c ft_memccpy.c ft_memcmp.c ft_strchr.c ft_strlcat.c ft_strncat.c ft_strncmp.c\
	ft_strrchr.c ft_strstr.c ft_strnstr.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c\
	ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c  ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c\
	ft_putchar.c ft_strtrim.c ft_strtrim.c ft_count_words.c ft_count_wordschr.c ft_strleni.c ft_strlenichr.c\
	ft_strsplit.c ft_itoa.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
	ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_test.c
OBJ =  $(SRC:.c=.o)

all: $(OBJ)

%.o: %.c
	@gcc -c $? -Wall -Wextra -Werror

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	
re: fclean all
